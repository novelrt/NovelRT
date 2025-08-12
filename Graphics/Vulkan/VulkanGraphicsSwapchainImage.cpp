// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics
{
    VkImageView CreateVulkanSwapChainImageView(std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> swapchain, VkImage image)
    {
        VkComponentMapping componentMapping{};
        componentMapping.r = VK_COMPONENT_SWIZZLE_R;
        componentMapping.g = VK_COMPONENT_SWIZZLE_G;
        componentMapping.b = VK_COMPONENT_SWIZZLE_B;
        componentMapping.a = VK_COMPONENT_SWIZZLE_A;

        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        VkImageViewCreateInfo swapChainImageViewCreateInfo{};
        swapChainImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        swapChainImageViewCreateInfo.image = image;
        swapChainImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        swapChainImageViewCreateInfo.format = swapchain->GetVulkanFormat();
        swapChainImageViewCreateInfo.components = componentMapping;
        swapChainImageViewCreateInfo.subresourceRange = subresourceRange;

        VkImageView swapChainImageView = VK_NULL_HANDLE;
        VkResult result = vkCreateImageView(swapchain->GetDevice()->GetVulkanDevice(), &swapChainImageViewCreateInfo, nullptr, &swapChainImageView);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise VkImageView instance with the given parameters and VkDevice.", result);
        }

        return swapChainImageView;
    }

    // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::shared_from_this()
    {
        return std::static_pointer_cast<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>(
            GraphicsDeviceObject::shared_from_this());
    }

    GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GraphicsSwapchainImage(
        std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> swapchain,
        VkImage image, uint32_t width, uint32_t height)
        : _swapchain(std::move(swapchain)),
          _image(image),
          _imageView(CreateVulkanSwapChainImageView(_swapchain, _image)),
          _width(width),
          _height(height)
    {
    }

    GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::~GraphicsSwapchainImage() noexcept
    {
        vkDestroyImageView(GetDevice()->GetVulkanDevice(), _imageView, nullptr);
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::GetDevice() const
    {
        return _swapchain->GetDevice();
    }

    std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::GetSwapchain() const
    {
        return _swapchain;
    }

    VkImage GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetVulkanImage() const noexcept
    {
        return _image;
    }

    VkImageView GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetVulkanImageView() const noexcept
    {
        return _imageView;
    }

    uint32_t GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetWidth() const noexcept
    {
        return _width;
    }

    uint32_t GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetHeight() const noexcept
    {
        return _height;
    }

    std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::CreateContext()
    {
        return std::make_shared<GraphicsContext<Vulkan::VulkanGraphicsBackend>>(shared_from_this());
    }
}
