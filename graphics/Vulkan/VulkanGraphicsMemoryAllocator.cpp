// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsMemoryAllocator::VulkanGraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                                                 std::shared_ptr<GraphicsAdapter> adapter,
                                                                 std::shared_ptr<GraphicsDevice> device)
        : GraphicsMemoryAllocator(provider, adapter, device), _allocator(VK_NULL_HANDLE)
    {
    }

    std::shared_ptr<GraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateBuffer(
        const GraphicsBufferCreateInfo& createInfo)
    {
        return nullptr;
    }

    std::shared_ptr<GraphicsTexture> VulkanGraphicsMemoryAllocator::CreateTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        return nullptr;
    }

    std::shared_ptr<VulkanGraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateVulkanBuffer(
        const GraphicsBufferCreateInfo& createInfo)
    {
        return nullptr;
    }

    std::shared_ptr<VulkanGraphicsTexture> VulkanGraphicsMemoryAllocator::CreateVulkanTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        return nullptr;
    }
}