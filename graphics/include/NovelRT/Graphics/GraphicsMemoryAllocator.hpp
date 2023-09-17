#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/TexelFormat.hpp>
#include <cstdint>
#include <memory>


namespace NovelRT::Graphics
{
    class GraphicsAdapter;
    class GraphicsDevice;
    class GraphicsProvider;
    class GraphicsBuffer;
    class GraphicsTexture;

    class GraphicsMemoryAllocator
    {
    private:
        std::shared_ptr<GraphicsProvider> _provider;
        std::shared_ptr<GraphicsAdapter> _adapter;
        std::shared_ptr<GraphicsDevice> _device;

    public:
        GraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                std::shared_ptr<GraphicsAdapter> adapter,
                                std::shared_ptr<GraphicsDevice> device);

        [[nodiscard]] std::shared_ptr<GraphicsProvider> GetProvider() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsAdapter> GetAdapter() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsDevice> GetDevice() const noexcept;
        [[nodiscard]] virtual std::shared_ptr<GraphicsBuffer> CreateBuffer(
            GraphicsBufferKind bufferKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            size_t size,
            GraphicsMemoryRegionAllocationFlags allocationFlags) = 0;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateBuffer(GraphicsBufferKind bufferKind,
                                                                   GraphicsResourceAccess cpuAccessKind,
                                                                   GraphicsResourceAccess gpuAccessKind,
                                                                   size_t size);

        [[nodiscard]] virtual std::shared_ptr<GraphicsTexture> CreateTexture(
            GraphicsTextureAddressMode addressMode,
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            GraphicsMemoryRegionAllocationFlags allocationFlags,
            TexelFormat texelFormat) = 0;

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTexture(GraphicsTextureAddressMode addressMode,
                                                                     GraphicsTextureKind textureKind,
                                                                     GraphicsResourceAccess cpuAccessKind,
                                                                     GraphicsResourceAccess gpuAccessKind,
                                                                     uint32_t width);

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTexture(GraphicsTextureAddressMode addressMode,
                                                                     GraphicsTextureKind textureKind,
                                                                     GraphicsResourceAccess cpuAccessKind,
                                                                     GraphicsResourceAccess gpuAccessKind,
                                                                     uint32_t width,
                                                                     uint32_t height);
    };
}