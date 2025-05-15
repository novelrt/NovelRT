#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <cstdint>
#include <memory>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsMemoryAllocator;

    template<template <typename TBackend> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsResource : public GraphicsDeviceObject<TBackend>, public std::enable_shared_from_this<GraphicsResource<TBackend>>
    {
    public:
        using BackendResourceType = typename GraphicsBackendTraits<TBackend>::ResourceType;

    protected:
        std::shared_ptr<BackendResourceType> _implementation;

    private:
        std::shared_ptr<GraphicsMemoryAllocator<TBackend>> _allocator;
        GraphicsResourceAccess _cpuAccess;

    public:
        using std::enable_shared_from_this<GraphicsResource>::shared_from_this;

        explicit GraphicsResource(std::shared_ptr<BackendResourceType> implementation,
                                  std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                                  GraphicsResourceAccess cpuAccess) noexcept
            : GraphicsDeviceObject<TBackend>(allocator->GetDevice()),
              _implementation(implementation),
              _allocator(allocator),
              _cpuAccess(cpuAccess)
        {
        }

        virtual ~GraphicsResource() noexcept override = default;

        //[[nodiscard]] virtual size_t GetAlignment() const noexcept = 0; //TODO: Do we still need this?
        [[nodiscard]] std::shared_ptr<GraphicsMemoryAllocator<TBackend>> GetAllocator() const noexcept
        {
            return _implementation->GetAllocator();
        }

        [[nodiscard]] GraphicsResourceAccess GetCpuAccess() const noexcept
        {
            return _implementation->GetCpuAccess();
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
            return _implementation->Allocate(size, alignment);
        }

        [[nodiscard]] Utilities::Misc::Span<uint8_t> MapBytes()
        {
            return MapBytes(0, GetSize());
        }

        [[nodiscard]] virtual Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength)
        {
            return _implementation->MapBytes(rangeOffset, rangeLength);
        }

        [[nodiscard]] Utilities::Misc::Span<const uint8_t> MapBytesForRead()
        {
            return MapBytesForRead(0, GetSize());
        }

        [[nodiscard]] Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength)
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

        template<typename T> [[nodiscard]] Utilities::Misc::Span<T> Map()
        {
            return Utilities::Misc::SpanCast<T>(MapBytes());
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<T> Map(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::Misc::SpanCast<T>(MapBytes(rangeOffset, rangeLength));
        }

        template <typename T, template <typename> typename TResource> [[nodiscard]] Utilities::Misc::Span<T> Map(std::shared_ptr<GraphicsResourceMemoryRegion<TResource, TBackend>> memoryRegion)
        {
            return Utilities::Misc::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<const T> MapForRead()
        {
            return Utilities::Misc::SpanCast<const T>(MapBytesForRead());
        }

        template<typename T>
        [[nodiscard]] Utilities::Misc::Span<const T> MapForRead(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::Misc::SpanCast<const T>(MapBytesForRead(rangeOffset, rangeLength));
        }

        template <template <typename> typename TResource> void UnmapAndWrite(std::shared_ptr<GraphicsResourceMemoryRegion<TResource, TBackend>> memoryRegion)
        {
            UnmapBytesAndWrite(memoryRegion->GetOffset(), memoryRegion->GetSize());
        }
    };
}
