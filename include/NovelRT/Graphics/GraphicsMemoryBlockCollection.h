// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSMEMORYBLOCKCOLLECTION_H
#define NOVELRT_GRAPHICS_GRAPHICSMEMORYBLOCKCOLLECTION_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsMemoryBlockCollection : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsMemoryAllocator> _allocator;
        std::vector<std::shared_ptr<GraphicsMemoryBlock>> _blocks;
        std::mutex _mutex;
        std::shared_ptr<GraphicsMemoryBlock> _emptyBlock;
        size_t _minimumSize;
        size_t _size;
        Threading::VolatileState _state;

        [[nodiscard]] std::shared_ptr<GraphicsMemoryBlock> AddBlock(size_t size);
        [[nodiscard]] size_t GetAdjustedBlockSize(size_t size) const noexcept;
        [[nodiscard]] size_t GetLargestSharedBlockSize() const noexcept;
        void IncrementallySortBlocks() noexcept;
        void RemoveBlock(const std::shared_ptr<GraphicsMemoryBlock>& block);
        void RemoveBlockAt(std::vector<std::shared_ptr<GraphicsMemoryBlock>>::iterator iterator);
        void RemoveBlockAt(size_t index);

        bool TryAllocateRegion(size_t size,
                               size_t alignment,
                               GraphicsMemoryRegionAllocationFlags flags,
                               GraphicsMemoryRegion<GraphicsMemoryBlock>& region);

    protected:
        [[nodiscard]] virtual GraphicsMemoryBlock* CreateBlock(size_t size) = 0;

    public:
        GraphicsMemoryBlockCollection(std::shared_ptr<GraphicsDevice> device,
                                      std::shared_ptr<GraphicsMemoryAllocator> allocator);

        [[nodiscard]] inline std::shared_ptr<GraphicsMemoryAllocator> GetAllocator() const noexcept
        {
            return _allocator;
        }

        [[nodiscard]] inline int32_t GetMaximumBlockCount() const noexcept
        {
            return _allocator->GetSettings().MaximumBlockCountPerCollection;
        }

        [[nodiscard]] inline size_t GetMaximumSharedBlockSize() const noexcept
        {
            return _allocator->GetSettings().MaximumSharedBlockSize.value_or(256 * 1024 * 1024);
        }

        [[nodiscard]] inline int32_t GetMinimumBlockCount() const noexcept
        {
            return _allocator->GetSettings().MinimumBlockCountPerCollection;
        }

        [[nodiscard]] inline size_t GetMinimumBlockSize() const noexcept
        {
            return _allocator->GetSettings().MinimumBlockSize;
        }

        [[nodiscard]] inline size_t GetMinimumSize() const noexcept
        {
            return _minimumSize;
        }

        [[nodiscard]] inline size_t GetSize() const noexcept
        {
            return _size;
        }

        [[nodiscard]] GraphicsMemoryRegion<GraphicsMemoryBlock> Allocate(
            size_t size,
            size_t alignment = 1,
            GraphicsMemoryRegionAllocationFlags flags = GraphicsMemoryRegionAllocationFlags::None);

        [[nodiscard]] bool TryAllocate(size_t size,
                                       size_t alignment,
                                       GraphicsMemoryRegionAllocationFlags flags,
                                       GraphicsMemoryRegion<GraphicsMemoryBlock>& outRegion);

        [[nodiscard]] bool TryAllocate(size_t size, GraphicsMemoryRegion<GraphicsMemoryBlock>& outRegion);

        [[nodiscard]] bool TryAllocate(
            size_t size,
            size_t alignment,
            GraphicsMemoryRegionAllocationFlags flags,
            NovelRT::Utilities::Misc::Span<GraphicsMemoryRegion<GraphicsMemoryBlock>> regions);

        [[nodiscard]] bool TryAllocate(
            size_t size,
            NovelRT::Utilities::Misc::Span<GraphicsMemoryRegion<GraphicsMemoryBlock>> regions);

        void Free(const GraphicsMemoryRegion<GraphicsMemoryBlock>& region);

        [[nodiscard]] inline std::vector<std::shared_ptr<GraphicsMemoryBlock>>::iterator begin() noexcept
        {
            return _blocks.begin();
        }

        [[nodiscard]] inline std::vector<std::shared_ptr<GraphicsMemoryBlock>>::iterator end() noexcept
        {
            return _blocks.end();
        }

        [[nodiscard]] inline std::vector<std::shared_ptr<GraphicsMemoryBlock>>::const_iterator begin() const noexcept
        {
            return _blocks.begin();
        }

        [[nodiscard]] inline std::vector<std::shared_ptr<GraphicsMemoryBlock>>::const_iterator end() const noexcept
        {
            return _blocks.end();
        }

        [[nodiscard]] inline std::vector<std::shared_ptr<GraphicsMemoryBlock>>::const_iterator cbegin() const noexcept
        {
            return _blocks.cbegin();
        }

        [[nodiscard]] inline std::vector<std::shared_ptr<GraphicsMemoryBlock>>::const_iterator cend() const noexcept
        {
            return _blocks.cend();
        }

        [[nodiscard]] bool TrySetMinimumSize(size_t minimumSize);
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSMEMORYBLOCKCOLLECTION_H
