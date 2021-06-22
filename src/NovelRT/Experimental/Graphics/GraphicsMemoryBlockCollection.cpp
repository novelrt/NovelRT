// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>
#include <NovelRT/Experimental/Graphics/GraphicsMemoryBlockCollection.h>

namespace NovelRT::Experimental::Graphics
{
    std::shared_ptr<GraphicsMemoryBlock> GraphicsMemoryBlockCollection::AddBlock(size_t size)
    {
        std::shared_ptr<GraphicsMemoryBlock> block = CreateBlock(size);

        _blocks.push_back(block);
        _size += size;

        return std::move(block);
    }

    size_t GraphicsMemoryBlockCollection::GetAdjustedBlockSize(size_t size) const noexcept
    {
        size_t maximumSharedBlockSize = GetMaximumSharedBlockSize();
        size_t blockSize = size;

        if (blockSize < maximumSharedBlockSize)
        {
            size_t minimumBlockSize = GetMinimumBlockSize();
            blockSize = GetMaximumSharedBlockSize();

            if (minimumBlockSize != maximumSharedBlockSize)
            {
                // Allocate 1/8, 1/4, 1/2 as first blocks, ensuring we don't go smaller than the minimum.
                size_t largestBlockSize = GetLargestSharedBlockSize();

                for (size_t i = 0ULL; i < 3; ++i)
                {
                    size_t smallerBlockSize = blockSize / 2ULL;

                    if ((smallerBlockSize > largestBlockSize) && (smallerBlockSize >= (size * 2ULL)))
                    {
                        blockSize = std::max(smallerBlockSize, minimumBlockSize);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            blockSize = size;
        }

        return blockSize;
    }

    size_t GraphicsMemoryBlockCollection::GetLargestSharedBlockSize() const noexcept
    {
        size_t result = 0ULL;
        gsl::span<const std::shared_ptr<GraphicsMemoryBlock>> blocks(&(*_blocks.begin()), _blocks.size());
        size_t maximumSharedBlockSize = GetMaximumSharedBlockSize();

        for (size_t i = blocks.size(); i-- != 0;)
        {
            size_t blockSize = blocks[i]->GetSize();

            if (blockSize < maximumSharedBlockSize)
            {
                result = std::max(result, blockSize);
            }
            else if (blockSize == maximumSharedBlockSize)
            {
                result = maximumSharedBlockSize;
                break;
            }
        }

        return result;
    }

    void GraphicsMemoryBlockCollection::IncrementallySortBlocks() noexcept
    {
        // Bubble sort only until first swap. This is called after
        // freeing a region and will result in eventual consistency.

        gsl::span<std::shared_ptr<GraphicsMemoryBlock>> blocks(&(*_blocks.begin()), _blocks.size());

        if (blocks.size() >= 2ULL)
        {
            std::shared_ptr<GraphicsMemoryBlock> previousBlock = blocks[0];

            for (size_t i = 1ULL; i < blocks.size(); ++i)
            {
                std::shared_ptr<GraphicsMemoryBlock> block = blocks[i];

                if (previousBlock->GetTotalFreeRegionSize() <= block->GetTotalFreeRegionSize())
                {
                    previousBlock = block;
                }
                else
                {
                    blocks[i - 1ULL] = block;
                    blocks[i] = previousBlock;
                    return;
                }
            }
        }
    }

    void GraphicsMemoryBlockCollection::RemoveBlock(const std::shared_ptr<GraphicsMemoryBlock>& block)
    {
        auto blockIndex = std::find(_blocks.begin(), _blocks.end(), block);
        RemoveBlockAt(blockIndex);
    }

    void GraphicsMemoryBlockCollection::RemoveBlockAt(
        std::vector<std::shared_ptr<GraphicsMemoryBlock>>::iterator iterator)
    {
        std::shared_ptr<GraphicsMemoryBlock> block = *iterator;
        _blocks.erase(iterator);
        _size -= block->GetSize();
    }

    void GraphicsMemoryBlockCollection::RemoveBlockAt(size_t index)
    {
        RemoveBlockAt(std::next(_blocks.begin(), static_cast<ptrdiff_t>(index)));
    }

    bool GraphicsMemoryBlockCollection::TryAllocateRegion(size_t size,
                                                          size_t alignment,
                                                          GraphicsMemoryRegionAllocationFlags flags,
                                                          GraphicsMemoryRegion<GraphicsMemoryBlock>& region)
    {
        bool useDedicatedBlock = (flags & GraphicsMemoryRegionAllocationFlags::DedicatedCollection) ==
                                 GraphicsMemoryRegionAllocationFlags::DedicatedCollection;

        bool useExistingBlock = (flags & GraphicsMemoryRegionAllocationFlags::ExistingCollection) ==
                                GraphicsMemoryRegionAllocationFlags::ExistingCollection;

        if (useDedicatedBlock && useExistingBlock)
        {
            throw std::out_of_range(
                "A region allocation request defined as requiring both a dedicated and existing block.");
        }

        GraphicsMemoryBudget budget =
            _allocator->GetBudget(std::dynamic_pointer_cast<GraphicsMemoryBlockCollection>(shared_from_this()));

        size_t maximumSharedBlockSize = GetMaximumSharedBlockSize();
        size_t sizeWithMargins =
            size + (2ULL * _allocator->GetSettings().MinimumAllocatedRegionMarginSize.value_or(0ULL));

        gsl::span<std::shared_ptr<GraphicsMemoryBlock>> blocks(&(*_blocks.begin()), _blocks.size());
        size_t blocksLength = blocks.size();

        size_t availableMemory = (budget.GetEstimatedUsage() < budget.GetEstimatedBudget())
                                     ? (budget.GetEstimatedBudget() - budget.GetEstimatedUsage())
                                     : 0ULL;

        bool canCreateNewBlock =
            !useExistingBlock && (blocksLength < GetMaximumBlockCount()) && (availableMemory >= sizeWithMargins);

        // 1. Search existing blocks.

        if (!useDedicatedBlock && (size <= maximumSharedBlockSize))
        {
            for (size_t blockIndex = 0ULL; blockIndex < blocksLength; ++blockIndex)
            {
                std::shared_ptr<GraphicsMemoryBlock> currentBlock = blocks[blockIndex];

                if (currentBlock == nullptr)
                {
                    throw Exceptions::NullPointerException("The memory block is set to nullptr.");
                }

                if (currentBlock->TryAllocate(size, alignment, region))
                {
                    if (currentBlock == _emptyBlock)
                    {
                        _emptyBlock = nullptr;
                    }
                    return true;
                }
            }
        }

        // 2. Try to create a new block.

        if (!canCreateNewBlock)
        {
            return false;
        }

        size_t blockSize = GetAdjustedBlockSize(sizeWithMargins);

        if (blockSize >= availableMemory)
        {
            return false;
        }

        std::shared_ptr<GraphicsMemoryBlock> block = AddBlock(blockSize);
        return block->TryAllocate(size, alignment, region);
    }

    GraphicsMemoryBlockCollection::GraphicsMemoryBlockCollection(std::shared_ptr<ILLGraphicsDevice> device,
                                                                 std::shared_ptr<GraphicsMemoryAllocator> allocator)
        : GraphicsDeviceObject(std::move(device)),
          _allocator(std::move(allocator)),
          _blocks{},
          _mutex(),
          _emptyBlock(nullptr),
          _minimumSize(0ULL),
          _size(0LL),
          _state()
    {
        if (_allocator == nullptr)
        {
            throw Exceptions::NullPointerException("Parameter name: allocator.");
        }

        if (_allocator->GetDevice() != GraphicsDeviceObject::GetDevice())
        {
            throw std::out_of_range(
                "The same graphics device is not being used for this memory block collection. It is out "
                "of range of one of the devices.");
        }

        const GraphicsMemoryAllocatorSettings& settings = _allocator->GetSettings();

        int32_t minimumBlockCount = settings.MinimumBlockCountPerCollection;
        size_t maximumSharedBlockSize = settings.MaximumSharedBlockSize.value_or(0ULL);

        for (size_t i = 0ULL; i < minimumBlockCount; ++i)
        {
            size_t blockSize = GetAdjustedBlockSize(maximumSharedBlockSize);
            static_cast<void>(AddBlock(blockSize));
        }

        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    GraphicsMemoryRegion<GraphicsMemoryBlock> GraphicsMemoryBlockCollection::Allocate(
        size_t size,
        size_t alignment,
        GraphicsMemoryRegionAllocationFlags flags)
    {
        GraphicsMemoryRegion<GraphicsMemoryBlock> outRegion(0ULL, nullptr, nullptr, false, 0ULL, 0ULL);
        bool succeeded = TryAllocate(size, alignment, flags, outRegion);

        if (!succeeded)
        {
            throw Exceptions::OutOfMemoryException("Attempted to allocate memory region of size: " +
                                                   std::to_string(size));
        }

        return outRegion;
    }

    void GraphicsMemoryBlockCollection::Free(const GraphicsMemoryRegion<GraphicsMemoryBlock>& region)
    {
        std::shared_ptr<GraphicsMemoryBlock> block = region.GetCollection();

        if (block == nullptr)
        {
            throw Exceptions::NullPointerException("The supplied memory region's collection is nullptr.");
        }

        std::lock_guard<std::mutex> guard(_mutex); // TODO: come back to this when Tanner gets back to you

        auto blockIndex = std::find(_blocks.begin(), _blocks.end(), block);

        if (blockIndex == _blocks.end())
        {
            throw Exceptions::KeyNotFoundException(); // TODO: custom message maybe?
        }

        block->Free(region);

        if (block->GetIsEmpty())
        {
            size_t blocksCount = _blocks.size();

            if (_emptyBlock != nullptr)
            {
                if (blocksCount > GetMinimumBlockCount())
                {
                    size_t size = GetSize();
                    size_t minimumSize = GetMinimumSize();

                    // We have two empty blocks, we want to prefer removing the larger of the two.

                    if (block->GetSize() > _emptyBlock->GetSize())
                    {
                        if ((size - block->GetSize()) >= minimumSize)
                        {
                            RemoveBlockAt(blockIndex);
                        }
                        else if ((size - _emptyBlock->GetSize()) >= minimumSize)
                        {
                            RemoveBlock(_emptyBlock);
                        }
                    }
                    else if ((size - _emptyBlock->GetSize()) >= minimumSize)
                    {
                        RemoveBlockAt(blockIndex);
                    }
                    else if ((size - block->GetSize()) >= minimumSize)
                    {
                        RemoveBlock(_emptyBlock);
                    }

                    // Removing either would put us below the minimum size if none of the above is met, so we can't
                    // remove.
                }
                else if (block->GetSize() > _emptyBlock->GetSize())
                {
                    _emptyBlock = block;
                }
            }
            else
            {
                // We have no existing empty blocks, so we want to set the index to this block unless
                // we are currently exceeding our memory budget, in which case we want to free the block
                // instead. However, we still need to maintain the minimum block count and minimum size
                // placed on the collection, so we will only respect the budget if those can be maintained.

                GraphicsMemoryBudget budget =
                    _allocator->GetBudget(std::static_pointer_cast<GraphicsMemoryBlockCollection>(shared_from_this()));

                if ((budget.GetEstimatedUsage() >= budget.GetEstimatedBudget()) &&
                    (blocksCount > GetMinimumBlockCount()) && ((GetSize() - block->GetSize()) >= GetMinimumSize()))
                {
                    RemoveBlockAt(blockIndex);
                }
                else
                {
                    _emptyBlock = block;
                }
            }
        }

        IncrementallySortBlocks();
    }

    bool GraphicsMemoryBlockCollection::TryAllocate(size_t size,
                                                    size_t alignment,
                                                    GraphicsMemoryRegionAllocationFlags flags,
                                                    GraphicsMemoryRegion<GraphicsMemoryBlock>& outRegion)
    {
        std::lock_guard<std::mutex> guard(_mutex); // TODO: come back to this when Tanner gets back to you
        return TryAllocateRegion(size, alignment, flags, outRegion);
    }

    bool GraphicsMemoryBlockCollection::TryAllocate(size_t size, GraphicsMemoryRegion<GraphicsMemoryBlock>& outRegion)
    {
        return TryAllocate(size, 1ULL, GraphicsMemoryRegionAllocationFlags::None, outRegion);
    }

    bool GraphicsMemoryBlockCollection::TryAllocate(size_t size,
                                                    size_t alignment,
                                                    GraphicsMemoryRegionAllocationFlags flags,
                                                    gsl::span<GraphicsMemoryRegion<GraphicsMemoryBlock>> regions)
    {
        bool succeeded = true;
        size_t index;

        // This scope is needed for the lock guard.
        {
            std::lock_guard<std::mutex> guard(_mutex); // TODO: come back to this when Tanner gets back to you

            for (index = 0ULL; index < regions.size(); ++index)
            {
                succeeded = TryAllocateRegion(size, alignment, flags, regions[index]);

                if (!succeeded)
                {
                    break;
                }
            }
        }

        if (!succeeded)
        {
            while (index-- != 0ULL)
            {
                Free(regions[index]);
                regions[index] = GraphicsMemoryRegion<GraphicsMemoryBlock>();
            }
        }

        return succeeded;
    }

    bool GraphicsMemoryBlockCollection::TryAllocate(size_t size,
                                                    gsl::span<GraphicsMemoryRegion<GraphicsMemoryBlock>> regions)
    {
        return TryAllocate(size, 1ULL, GraphicsMemoryRegionAllocationFlags::None, regions);
    }

    bool GraphicsMemoryBlockCollection::TrySetMinimumSize(size_t minimumSize)
    {
        std::lock_guard<std::mutex> guard(_mutex); // TODO: come back to this when Tanner gets back to you

        size_t currentMinimumSize = GetMinimumSize();

        if (minimumSize == currentMinimumSize)
        {
            return true;
        }

        size_t size = GetSize();
        size_t blockCount = _blocks.size();

        if (minimumSize < currentMinimumSize)
        {
            std::shared_ptr<GraphicsMemoryBlock> emptyBlock = nullptr;
            size_t minimumBlockCount = GetMinimumBlockCount();

            for (size_t blockIndex = blockCount; blockIndex-- != 0ULL;)
            {
                std::shared_ptr<GraphicsMemoryBlock> block = _blocks[blockIndex];

                size_t blockSize = block->GetSize();
                bool blockIsEmpty = block->GetIsEmpty();

                if (blockIsEmpty)
                {
                    if (((size - blockSize) >= minimumSize) && ((blockCount - 1) >= minimumBlockCount))
                    {
                        RemoveBlockAt(blockIndex);
                        size -= blockSize;
                        --blockCount;
                    }
                    else
                    {
                        emptyBlock = (emptyBlock == nullptr) ? block : emptyBlock;
                    }
                }
            }
            _emptyBlock = emptyBlock;
        }
        else
        {
            std::shared_ptr<GraphicsMemoryBlock> emptyBlock = nullptr;
            size_t maximumBlockCount = GetMaximumBlockCount();
            size_t maximumSharedBlockSize = GetMaximumSharedBlockSize();
            size_t minimumBlockSize = GetMinimumBlockSize();

            while (size < minimumSize)
            {
                if (blockCount < maximumBlockCount)
                {
                    size_t blockSize = GetAdjustedBlockSize(maximumSharedBlockSize);

                    if (((size + blockSize) > minimumSize) && (blockSize != minimumBlockSize))
                    {
                        blockSize = minimumSize - size;
                    }

                    emptyBlock = (emptyBlock == nullptr) ? AddBlock(blockSize) : emptyBlock;
                    size += blockSize;
                }
                else
                {
                    _emptyBlock = (_emptyBlock == nullptr) ? emptyBlock : _emptyBlock;
                    return false;
                }
            }

            _emptyBlock = (_emptyBlock == nullptr) ? emptyBlock : _emptyBlock;

        }

        _minimumSize = minimumSize;
        if (_size != size)
        {
            throw std::runtime_error("Sizes don't match!"); // TODO: Make this a real exception later maybe? or just
            // put it in debug builds only?
        }
        return true;
    }
} // namespace NovelRT::Experimental::Graphics