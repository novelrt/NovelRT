#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <cstdint>

namespace NovelRT::Graphics
{
    template<typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsTexture : public GraphicsResource<TBackend>
    {
    public:
        using BackendTextureType = typename GraphicsBackendTraits<TBackend>::TextureType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::ResourceMemoryRegionType;

    private:
        GraphicsTextureAddressMode _addressMode;
        GraphicsTextureKind _kind;
        uint32_t _width;
        uint32_t _height;
        uint16_t _depth;

    public:
        GraphicsTexture(std::shared_ptr<BackendTextureType> implementation,
                        std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                        GraphicsResourceAccess cpuAccess,
                        GraphicsTextureAddressMode addressMode,
                        GraphicsTextureKind kind,
                        uint32_t width,
                        uint32_t height,
                        uint16_t depth) noexcept
            : GraphicsResource(implementation, allocator, cpuAccess),
              _kind(kind),
              _width(width),
              _height(height),
              _depth(depth)
        {
        }

        virtual ~GraphicsTexture() noexcept override = default;

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> Allocate(
            size_t size,
            size_t alignment)
        {
            return GraphicsResource<TBackend>::_implementation->Allocate(size, alignment);
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