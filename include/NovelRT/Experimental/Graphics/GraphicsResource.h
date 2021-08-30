// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsResource : public GraphicsDeviceObject, public IGraphicsMemoryRegionCollection<GraphicsResource>
    {
    private:
        GraphicsMemoryRegion<GraphicsMemoryBlock> _blockRegion;
        std::shared_ptr<GraphicsMemoryAllocator> _allocator;
        GraphicsResourceCpuAccessKind _cpuAccess;

    public:
        GraphicsResource(const std::shared_ptr<GraphicsDevice>& device,
                         GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                         GraphicsResourceCpuAccessKind cpuAccess)
            : GraphicsDeviceObject(std::weak_ptr<GraphicsDevice>(device)), _blockRegion(std::move(blockRegion)), _cpuAccess(cpuAccess)
        {
            if (_blockRegion.GetCollection() == nullptr)
            {
                throw Exceptions::NullPointerException("The collection in the provided block region is null.");
            }

            // Explicit call to base GetDevice() to avoid ambiguity in the ctor.
            if (_blockRegion.GetDevice() != GraphicsDeviceObject::GetDevice())
            {
                throw std::out_of_range("The device of the block region does not match that of the provided device. "
                                        "This resource will be out of range and therefore invalid.");
            }

            _allocator = _blockRegion.GetCollection()->GetCollection()->GetAllocator();
        }

        [[nodiscard]] inline size_t GetAlignment() const noexcept
        {
            return GetBlockRegion().GetAlignment();
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsMemoryAllocator> GetAllocator() const noexcept
        {
            return _allocator;
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsMemoryBlock> GetBlock() const noexcept
        {
            return GetBlockRegion().GetCollection();
        }

        [[nodiscard]] inline const GraphicsMemoryRegion<GraphicsMemoryBlock>& GetBlockRegion() const noexcept
        {
            return _blockRegion;
        }

        [[nodiscard]] virtual int32_t GetCount() const noexcept = 0;

        [[nodiscard]] inline GraphicsResourceCpuAccessKind GetCpuAccess() const noexcept
        {
            return _cpuAccess;
        }

        [[nodiscard]] inline size_t GetOffset() const noexcept
        {
            return GetBlockRegion().GetOffset();
        }

        [[nodiscard]] inline size_t GetSize() const noexcept final
        {
            return GetBlockRegion().GetSize();
        }

        [[nodiscard]] virtual void* MapUntyped() = 0;

        [[nodiscard]] virtual void* MapUntyped(size_t rangeOffset, size_t rangeLength) = 0;

        template<typename T> [[nodiscard]] T* Map()
        {
            return reinterpret_cast<T*>(MapUntyped());
        }

        template<typename T> [[nodiscard]] T* Map(const GraphicsMemoryRegion<GraphicsResource>& region)
        {
            return Map<T>(region.GetOffset(), region.GetSize());
        }

        template<typename T> [[nodiscard]] T* Map(size_t rangeOffset, size_t rangeLength)
        {
            return reinterpret_cast<T*>(MapUntyped(rangeOffset, rangeLength));
        }

        [[nodiscard]] virtual const void* MapForReadUntyped() = 0;
        [[nodiscard]] virtual const void* MapForReadUntyped(size_t readRangeOffset, size_t readRangeLength) = 0;

        template<typename T> [[nodiscard]] const T* MapForRead()
        {
            return reinterpret_cast<const T*>(MapForReadUntyped());
        }

        template<typename T> [[nodiscard]] const T* MapForRead(const GraphicsMemoryRegion<GraphicsResource>& readRegion)
        {
            return MapForRead<T>(readRegion.GetOffset(), readRegion.GetSize());
        }

        template<typename T> [[nodiscard]] const T* MapForRead(size_t readRangeOffset, size_t readRangeLength)
        {
            return reinterpret_cast<const T*>(MapForReadUntyped(readRangeOffset, readRangeLength));
        }

        virtual void Unmap() = 0;
        virtual void UnmapAndWrite() = 0;
        virtual void UnmapAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) = 0;

        inline void UnmapAndWrite(const GraphicsMemoryRegion<GraphicsResource>& writtenRegion)
        {
            UnmapAndWrite(writtenRegion.GetOffset(), writtenRegion.GetSize());
        }
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCE_H
