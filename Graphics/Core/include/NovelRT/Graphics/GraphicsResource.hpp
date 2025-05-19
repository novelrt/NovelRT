#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <cstdint>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsMemoryAllocator;

    template<template <typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsResource : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendResourceType = typename GraphicsBackendTraits<TBackend>::ResourceType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<BackendResourceType>;

    private:
        std::unique_ptr<BackendResourceType> _implementation;
        std::shared_ptr<GraphicsMemoryAllocator<TBackend>> _allocator;
        GraphicsResourceAccess _cpuAccess;

    protected:
        [[nodiscard]] std::unique_ptr<BackendResourceMemoryRegionType> AllocateInternal(
            size_t size,
            size_t alignment)
        {
            return _implementation->Allocate(size, alignment);
        }

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsResource<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsResource<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this());
        }

        explicit GraphicsResource(std::unique_ptr<BackendResourceType> implementation,
                                  std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                                  GraphicsResourceAccess cpuAccess) noexcept
            : GraphicsDeviceObject<TBackend>(allocator->GetDevice())
            , _implementation(std::move(implementation))
            , _allocator(std::move(allocator))
            , _cpuAccess(cpuAccess)
        {
        }

        virtual ~GraphicsResource() noexcept override = default;

        [[nodiscard]] BackendResourceType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] GraphicsMemoryAllocator<TBackend>* GetAllocator() const noexcept
        {
            return _allocator.get();
        }

        [[nodiscard]] GraphicsResourceAccess GetCpuAccess() const noexcept
        {
            return _cpuAccess;
        }

        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept
        {
            return _implementation->GetDeviceMemoryOffset();
        }

        [[nodiscard]] size_t GetSize() const noexcept
        {
            return _implementation->GetSize();
        }

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>> Allocate(
            size_t size,
            size_t alignment)
        {
            return std::make_shared<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>(
                std::move(AllocateInternal(size, alignment)),
                this->shared_from_this());
        }

        [[nodiscard]] Utilities::Span<uint8_t> MapBytes()
        {
            return MapBytes(0, GetSize());
        }

        [[nodiscard]] Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength)
        {
            return _implementation->MapBytes(rangeOffset, rangeLength);
        }

        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead()
        {
            return MapBytesForRead(0, GetSize());
        }

        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength)
        {
            return _implementation->MapBytesForRead(rangeOffset, rangeLength);
        }

        void UnmapBytes()
        {
            return _implementation->UnmapBytes();
        }

        void UnmapBytesAndWrite()
        {
            UnmapBytesAndWrite(0, GetSize());
        }

        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
        {
            return _implementation->UnmapBytesAndWrite(writtenRangeOffset, writtenRangeLength);
        }

        template<typename T> [[nodiscard]] Utilities::Span<T> Map()
        {
            return Utilities::SpanCast<T>(MapBytes());
        }

        template<typename T> [[nodiscard]] Utilities::Span<T> Map(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::SpanCast<T>(MapBytes(rangeOffset, rangeLength));
        }

        template <typename T> [[nodiscard]] Utilities::Span<T> Map(const GraphicsResourceMemoryRegion<GraphicsResource, TBackend>* memoryRegion)
        {
            return Utilities::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }

        template<typename T> [[nodiscard]] Utilities::Span<const T> MapForRead()
        {
            return Utilities::SpanCast<const T>(MapBytesForRead());
        }

        template<typename T>
        [[nodiscard]] Utilities::Span<const T> MapForRead(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::SpanCast<const T>(MapBytesForRead(rangeOffset, rangeLength));
        }

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsResource, TBackend>* memoryRegion)
        {
            UnmapBytesAndWrite(memoryRegion->GetOffset(), memoryRegion->GetSize());
        }
    };
}
