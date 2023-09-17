// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>

namespace NovelRT::Graphics
{
    GraphicsMemoryAllocator::GraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                                     std::shared_ptr<GraphicsAdapter> adapter,
                                                     std::shared_ptr<GraphicsDevice> device)
        : _provider(provider), _adapter(_adapter), _device(device)
    {
    }

    std::shared_ptr<GraphicsProvider> GraphicsMemoryAllocator::GetProvider() const noexcept
    {
        return _provider;
    }

    std::shared_ptr<GraphicsAdapter> GraphicsMemoryAllocator::GetAdapter() const noexcept
    {
        return _adapter;
    }

    std::shared_ptr<GraphicsDevice> GraphicsMemoryAllocator::GetDevice() const noexcept
    {
        return _device;
    }

    std::shared_ptr<GraphicsBuffer> GraphicsMemoryAllocator::CreateBuffer(
        GraphicsBufferKind bufferKind,
        GraphicsResourceAccess cpuAccessKind,
        GraphicsResourceAccess gpuAccessKind,
        size_t size)
    {
        return CreateBuffer(bufferKind, cpuAccessKind, gpuAccessKind, size,
                            GraphicsMemoryRegionAllocationFlags::None);
    }

    std::shared_ptr<GraphicsTexture> GraphicsMemoryAllocator::CreateTexture(
        GraphicsTextureAddressMode addressMode,
        GraphicsTextureKind textureKind,
        GraphicsResourceAccess cpuAccessKind,
        GraphicsResourceAccess gpuAccessKind,
        uint32_t width)
    {
        return CreateTexture(addressMode, textureKind, cpuAccessKind, gpuAccessKind, width, 1);
    }

    std::shared_ptr<GraphicsTexture> GraphicsMemoryAllocator::CreateTexture(
        GraphicsTextureAddressMode addressMode,
        GraphicsTextureKind textureKind,
        GraphicsResourceAccess cpuAccessKind,
        GraphicsResourceAccess gpuAccessKind,
        uint32_t width,
        uint32_t height)
    {
        return CreateTexture(addressMode, textureKind, cpuAccessKind, gpuAccessKind, width, height, 1,
                             GraphicsMemoryRegionAllocationFlags::None, TexelFormat::R8G8B8A8_UNORM);
    }
}

