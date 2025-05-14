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
    template<template <typename TBackend> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsTexture : public GraphicsResource<TBackend>, public std::enable_shared_from_this<GraphicsTexture<TBackend>>
    {
    public:
        using BackendTextureType = typename GraphicsBackendTraits<TBackend>::TextureType;
        using BackendResourceType = BackendTextureType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<BackendResourceType>;

    private:
        GraphicsTextureAddressMode _addressMode;
        GraphicsTextureKind _kind;
        uint32_t _width;
        uint32_t _height;
        uint16_t _depth;

    public:
        using std::enable_shared_from_this<GraphicsTexture>::shared_from_this;

        GraphicsTexture(std::shared_ptr<BackendTextureType> implementation,
                        std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                        const GraphicsTextureCreateInfo& createInfo) noexcept
            : GraphicsResource<TBackend>(implementation, allocator, createInfo.cpuAccessKind),
              _addressMode(createInfo.addressMode),
              _kind(createInfo.textureKind),
              _width(createInfo.width),
              _height(createInfo.height),
              _depth(createInfo.depth)
        {
        }

        virtual ~GraphicsTexture() noexcept override = default;

        [[nodiscard]] std::shared_ptr<BackendTextureType> GetImplementation() const noexcept
        {
            return std::static_pointer_cast<BackendTextureType>(GraphicsResource<TBackend>::_implementation);
        }

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> Allocate(
            size_t size,
            size_t alignment)
        {
            return std::make_shared<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>>(
                std::static_pointer_cast<BackendResourceMemoryRegionType>(GraphicsResource<TBackend>::_implementation->Allocate(size, alignment)),
                this->shared_from_this());
        }

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
    };
}
