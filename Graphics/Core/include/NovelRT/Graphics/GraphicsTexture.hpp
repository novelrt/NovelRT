#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTextureCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <cstdint>

namespace NovelRT::Graphics
{
    template<template <typename> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsTexture : public GraphicsResource<TBackend>
    {
    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsTexture<TBackend>> shared_from_this();

        GraphicsTexture() = delete;
        ~GraphicsTexture() noexcept final;

        [[nodiscard]] GraphicsTextureAddressMode GetAddressMode() const noexcept;
        [[nodiscard]] GraphicsTextureKind GetKind() const noexcept;

        [[nodiscard]] uint32_t GetWidth() const noexcept;
        [[nodiscard]] uint32_t GetHeight() const noexcept;
        [[nodiscard]] uint32_t GetDepth() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> Allocate(size_t size, size_t alignment);

        void UnmapBytes() final;

        void UnmapBytesAndWrite() final;
        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>* memoryRegion);

        template <typename T> [[nodiscard]] Utilities::Span<T> Map(const GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>* memoryRegion)
        {
            return Utilities::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }
    };
}
