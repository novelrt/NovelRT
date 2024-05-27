// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    GraphicsTexture::GraphicsTexture(std::shared_ptr<GraphicsDevice> device,
                                     std::shared_ptr<GraphicsMemoryAllocator> allocator,
                                     GraphicsResourceAccess cpuAccess,
                                     GraphicsTextureAddressMode addressMode,
                                     GraphicsTextureKind kind,
                                     uint32_t width,
                                     uint32_t height,
                                     uint16_t depth)
        : GraphicsResource(device, allocator, cpuAccess), _addressMode(addressMode), _kind(kind), _width(width), _height(height), _depth(depth)
    {
    }
    
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture>>  GraphicsTexture::Allocate(size_t size, size_t alignment)
    {
        GraphicsResource::Allocate(size, alignment);
    }

    GraphicsTextureAddressMode GraphicsTexture::GetAddressMode() const noexcept
    {
        return _addressMode;
    }

    GraphicsTextureKind GraphicsTexture::GetKind() const noexcept
    {
        return _kind;
    }

    uint32_t GraphicsTexture::GetWidth() const noexcept
    {
        return _width;
    }

    uint32_t GraphicsTexture::GetHeight() const noexcept
    {
        return _height;
    }

    uint16_t GraphicsTexture::GetDepth() const noexcept
    {
        return _depth;
    }
}