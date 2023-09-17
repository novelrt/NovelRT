#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsTexture;
    class VulkanGraphicsBuffer;

    class VulkanGraphicsMemoryAllocator final : public GraphicsMemoryAllocator
    {
    private:
    public:
        VulkanGraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                      std::shared_ptr<GraphicsAdapter> adapter,
                                      std::shared_ptr<GraphicsDevice> device);

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateBuffer(
            GraphicsBufferKind bufferKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            size_t size,
            GraphicsMemoryRegionAllocationFlags allocationFlags) final;

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTexture(
            GraphicsTextureAddressMode addressMode,
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            GraphicsMemoryRegionAllocationFlags allocationFlags,
            TexelFormat texelFormat) final;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsBuffer> CreateVulkanBuffer(
            GraphicsBufferKind bufferKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            size_t size,
            GraphicsMemoryRegionAllocationFlags allocationFlags);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsTexture> CreateVulkanTexture(
            GraphicsTextureAddressMode addressMode,
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            GraphicsMemoryRegionAllocationFlags allocationFlags,
            TexelFormat texelFormat);
    };
}