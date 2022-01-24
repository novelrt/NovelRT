// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSMEMORYREGION_H
#define NOVELRT_GRAPHICS_GRAPHICSMEMORYREGION_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    template<typename TCollection> class GraphicsMemoryRegion
    {
    private:
        size_t _alignment;
        std::shared_ptr<TCollection> _collection;
        std::shared_ptr<GraphicsDevice> _device;
        bool _isAllocated;
        size_t _offset;
        size_t _size;

    public:
        GraphicsMemoryRegion(size_t alignment,
                             std::shared_ptr<TCollection> collection,
                             std::shared_ptr<GraphicsDevice> device,
                             bool isAllocated,
                             size_t offset,
                             size_t size) noexcept
            : _alignment(alignment),
              _collection(std::move(collection)),
              _device(std::move(device)),
              _isAllocated(isAllocated),
              _offset(offset),
              _size(size)
        {
        }

        GraphicsMemoryRegion() noexcept
            : _alignment(0), _collection(nullptr), _device(nullptr), _isAllocated(false), _offset(0), _size(0)
        {
        }

        [[nodiscard]] size_t GetAlignment() const noexcept
        {
            return _alignment;
        }

        [[nodiscard]] std::shared_ptr<TCollection> GetCollection() const noexcept
        {
            return _collection;
        }

        [[nodiscard]] std::shared_ptr<GraphicsDevice> GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] bool GetIsAllocated() const noexcept
        {
            return _isAllocated;
        }

        [[nodiscard]] size_t GetOffset() const noexcept
        {
            return _offset;
        }

        [[nodiscard]] size_t GetSize() const noexcept
        {
            return _size;
        }

        [[nodiscard]] bool operator==(const GraphicsMemoryRegion<TCollection>& rhs) const noexcept
        {
            return (GetCollection() == rhs.GetCollection()) && (GetIsAllocated() == rhs.GetIsAllocated()) &&
                   (GetOffset() == rhs.GetOffset()) && (GetSize() == rhs.GetSize()) &&
                   (GetAlignment() == rhs.GetAlignment());
        }

        [[nodiscard]] bool operator!=(const GraphicsMemoryRegion<TCollection>& rhs) const noexcept
        {
            return !(*this == rhs);
        }
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSMEMORYREGION_H
