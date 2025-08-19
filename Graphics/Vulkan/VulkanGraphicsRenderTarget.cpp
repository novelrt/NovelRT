// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

namespace NovelRT::Graphics
{
    VkFramebuffer CreateVulkanFramebuffer(VkDevice device,
                                          VkRenderPass renderPass,
                                          Utilities::Span<VkImageView> imageViews,
                                          uint32_t width,
                                          uint32_t height,
                                          uint32_t layers = 1)
    {
        VkFramebufferCreateInfo framebufferCreateInfo{};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = renderPass;
        framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(imageViews.size());
        framebufferCreateInfo.pAttachments = imageViews.data();
        framebufferCreateInfo.width = width;
        framebufferCreateInfo.height = height;
        framebufferCreateInfo.layers = layers;

        VkFramebuffer vulkanFramebuffer = VK_NULL_HANDLE;
        const VkResult result = vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &vulkanFramebuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkFramebuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanFramebuffer;
    }

    GraphicsRenderTarget<Vulkan::VulkanGraphicsBackend>::GraphicsRenderTarget(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        Utilities::Span<VkImageView> imageViews,
        const std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>>& renderPass,
        uint32_t width,
        uint32_t height)
        : _device(std::move(device)), _framebuffer(VK_NULL_HANDLE)
    {

        _framebuffer = CreateVulkanFramebuffer(_device->GetVulkanDevice(), renderPass->GetVulkanRenderPass(),
                                               imageViews, width, height);
    }

    GraphicsRenderTarget<Vulkan::VulkanGraphicsBackend>::~GraphicsRenderTarget() noexcept
    {
        vkDestroyFramebuffer(_device->GetVulkanDevice(), _framebuffer, nullptr);
        _framebuffer = VK_NULL_HANDLE;
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GraphicsRenderTarget<
        Vulkan::VulkanGraphicsBackend>::GetDevice() const noexcept
    {
        return _device;
    }

    VkFramebuffer GraphicsRenderTarget<Vulkan::VulkanGraphicsBackend>::GetVulkanFramebuffer() const noexcept
    {
        return _framebuffer;
    }
}
