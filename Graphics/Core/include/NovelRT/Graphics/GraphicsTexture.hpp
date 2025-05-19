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
    private:
        using SuperBackendResourceType = typename GraphicsBackendTraits<TBackend>::ResourceType;
    public:
        using BackendResourceType = typename GraphicsBackendTraits<TBackend>::TextureType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<BackendResourceType>;

    private:
        GraphicsTextureAddressMode _addressMode;
        GraphicsTextureKind _kind;
        uint32_t _width;
        uint32_t _height;
        uint16_t _depth;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsTexture<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsTexture<TBackend>>(GraphicsResource<TBackend>::shared_from_this());
        }

        GraphicsTexture(std::unique_ptr<BackendResourceType> implementation,
                        std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                        const GraphicsTextureCreateInfo& createInfo) noexcept
            : GraphicsResource<TBackend>(
                NovelRT::Utilities::StaticPointerCast<SuperBackendResourceType>(std::move(implementation)),
                std::move(allocator),
                createInfo.cpuAccessKind)
            , _addressMode(createInfo.addressMode)
            , _kind(createInfo.textureKind)
            , _width(createInfo.width)
            , _height(createInfo.height)
            , _depth(static_cast<uint16_t>(createInfo.depth)) // TODO: Figure this out later, seems wrong
        {
        }

        virtual ~GraphicsTexture() noexcept override = default;

        [[nodiscard]] GraphicsTextureAddressMode GetAddressMode() const noexcept
        {
            return _addressMode;
        }

        [[nodiscard]] GraphicsTextureKind GetKind() const noexcept
        {
            return _kind;
        }

        [[nodiscard]] uint32_t GetWidth() const noexcept
        {
            return _width;
        }

        [[nodiscard]] uint32_t GetHeight() const noexcept
        {
            return _height;
        }

        [[nodiscard]] uint16_t GetDepth() const noexcept
        {
            return _depth;
        }

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> Allocate(
            size_t size,
            size_t alignment)
        {
            return std::make_shared<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>>(
                NovelRT::Utilities::StaticPointerCast<BackendResourceMemoryRegionType>(
                    std::move(GraphicsResource<TBackend>::AllocateInternal(size, alignment))),
                this->shared_from_this());
        }

        [[nodiscard]] BackendResourceType* GetImplementation() const noexcept
        {
            return static_cast<BackendResourceType*>(GraphicsResource<TBackend>::GetImplementation());
        }

        template <typename T> [[nodiscard]] Utilities::Span<T> Map(const GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>* memoryRegion)
        {
            return Utilities::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>* memoryRegion)
        {
            GraphicsResource<TBackend>::UnmapBytesAndWrite(memoryRegion->GetOffset(), memoryRegion->GetSize());
        }
    };
}
