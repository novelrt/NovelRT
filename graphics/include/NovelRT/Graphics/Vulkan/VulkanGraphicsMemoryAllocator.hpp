#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <vk_mem_alloc.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsTexture;
    class VulkanGraphicsBuffer;

    class VulkanGraphicsMemoryAllocator final : public GraphicsMemoryAllocator
    {
    private:
    VmaAllocator _allocator;

    public:
        VulkanGraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                      std::shared_ptr<GraphicsAdapter> adapter,
                                      std::shared_ptr<GraphicsDevice> device);

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateBuffer(const GraphicsBufferCreateInfo& createInfo) final;

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTexture(const GraphicsTextureCreateInfo& createInfo) final;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsBuffer> CreateVulkanBuffer(const GraphicsBufferCreateInfo& createInfo);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsTexture> CreateVulkanTexture(const GraphicsTextureCreateInfo& createInfo);
    };
}