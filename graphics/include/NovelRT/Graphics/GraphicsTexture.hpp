#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <cstdint>

namespace NovelRT::Graphics
{
    class GraphicsTexture : public GraphicsResource
    {
    private:
        GraphicsTextureAddressMode _addressMode;
        GraphicsTextureKind _kind;
        uint32_t _width;
        uint32_t _height;
        uint16_t _depth;

    public:
        GraphicsTexture(std::shared_ptr<GraphicsDevice> device,
                        std::shared_ptr<GraphicsMemoryAllocator> allocator,
                        GraphicsResourceAccess cpuAccess,
                        GraphicsTextureAddressMode addressMode,
                        GraphicsTextureKind kind,
                        uint32_t width,
                        uint32_t height,
                        uint16_t depth);
        
        virtual ~GraphicsTexture() noexcept override = default;

        [[nodiscard]] GraphicsTextureAddressMode GetAddressMode() const noexcept;
        
        [[nodiscard]] GraphicsTextureKind GetKind() const noexcept;

        [[nodiscard]] uint32_t GetWidth() const noexcept;
        
        [[nodiscard]] uint32_t GetHeight() const noexcept;

        [[nodiscard]] uint16_t GetDepth() const noexcept;
    };
}