#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <cstdint>
#include <memory>

namespace NovelRT::Graphics
{
    template <typename TBackend>
    class GraphicsMemoryAllocator;

    template<template <typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion;

    template<typename TBackend> class GraphicsResource : public GraphicsDeviceObject<TBackend>
    {
    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsResource<TBackend>> shared_from_this();

        GraphicsResource() = delete;
        virtual ~GraphicsResource() noexcept override = default;

        [[nodiscard]] std::weak_ptr<GraphicsMemoryAllocator<TBackend>> GetAllocator() const noexcept;
        [[nodiscard]] GraphicsResourceAccess GetCpuAccess() const noexcept;
        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept;
        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>> Allocate(size_t size, size_t alignment);

        [[nodiscard]] virtual Utilities::Span<uint8_t> MapBytes() = 0;
        [[nodiscard]] virtual Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) = 0;

        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead();
        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength);

        virtual void UnmapBytes() = 0;

        virtual void UnmapBytesAndWrite() = 0;
        virtual void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) = 0;

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsResource, TBackend>* memoryRegion);

        template<typename T>
        [[nodiscard]] Utilities::Span<T> Map()
        {
            return Utilities::SpanCast<T>(MapBytes());
        }
        template<typename T>
        [[nodiscard]] Utilities::Span<T> Map(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::SpanCast<T>(MapBytes(rangeOffset, rangeLength));
        }
        template <typename T>
        [[nodiscard]] Utilities::Span<T> Map(const GraphicsResourceMemoryRegion<GraphicsResource, TBackend>* memoryRegion)
        {
            return Utilities::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }

        template<typename T>
        [[nodiscard]] Utilities::Span<const T> MapForRead()
        {
            return Utilities::SpanCast<const T>(MapBytesForRead());
        }
        template<typename T>
        [[nodiscard]] Utilities::Span<const T> MapForRead(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::SpanCast<const T>(MapBytesForRead(rangeOffset, rangeLength));
        }
    };
}
