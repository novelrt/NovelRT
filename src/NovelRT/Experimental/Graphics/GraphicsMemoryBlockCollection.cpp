// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>
#include <NovelRT/Experimental/Graphics/GraphicsMemoryBlockCollection.h>

namespace NovelRT::Experimental::Graphics
{

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
            static_cast<void>(AddBlock());
        }

        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    GraphicsMemoryRegion<GraphicsMemoryBlock> GraphicsMemoryBlockCollection::Allocate(
        size_t size,
        size_t alignment,
        GraphicsMemoryRegionAllocationFlags flags)
    {

    }

    void GraphicsMemoryBlockCollection::Free(const GraphicsMemoryRegion<GraphicsMemoryBlock>& region)
    {
    }
}