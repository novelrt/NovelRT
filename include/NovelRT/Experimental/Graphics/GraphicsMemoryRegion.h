// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSMEMORYREGION_H
#define NOVELRT_GRAPHICSMEMORYREGION_H

namespace NovelRT::Experimental::Graphics
{
    template<typename TCollection> class GraphicsMemoryRegion
    {
    private:
        size_t _alignment;
        std::shared_ptr<TCollection> _collection;
        std::shared_ptr<ILLGraphicsDevice> _device;
        bool _isAllocated;
        size_t _offset;
        size_t _size;

    public:
        GraphicsMemoryRegion(size_t alignment,
                             std::shared_ptr<TCollection> collection,
                             std::shared_ptr<ILLGraphicsDevice> device,
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

        [[nodiscard]] size_t GetAlignment() const noexcept
        {
            return _alignment;
        }

        [[nodiscard]] std::shared_ptr<TCollection> GetCollection() const noexcept
        {
            return _collection;
        }

        [[nodiscard]] std::shared_ptr<ILLGraphicsDevice> GetDevice() const noexcept
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
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_GRAPHICSMEMORYREGION_H
