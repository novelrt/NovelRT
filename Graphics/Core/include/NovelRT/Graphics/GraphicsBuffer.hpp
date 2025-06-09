#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    template<template<typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion;

    template<typename TBackend>
    struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsBuffer final : public GraphicsResource<TBackend>
    {
    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsBuffer<TBackend>> shared_from_this();

        GraphicsBuffer() noexcept = delete;
        ~GraphicsBuffer() noexcept final;

        [[nodiscard]] GraphicsResourceAccess GetAccess() const noexcept;
        [[nodiscard]] GraphicsBufferKind GetKind();

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> Allocate(
            size_t size,
            size_t alignment);

        void Free(GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>& region);

        [[nodiscard]] Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) final;
        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength) final;

        void UnmapBytes() final;

        void UnmapBytesAndWrite() final;
        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        void UnmapAndWrite(const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>& memoryRegion);

        template<typename T>
        [[nodiscard]] Utilities::Span<T> Map(
            const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>& memoryRegion)
        {
            return Utilities::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }
    };
}
