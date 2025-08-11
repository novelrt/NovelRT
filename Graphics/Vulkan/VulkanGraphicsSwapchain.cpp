// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Support.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics
{
    VkSurfaceFormatKHR GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::ChooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept
    {
        VkSurfaceFormatKHR returnFormat{};
        returnFormat.format = VK_FORMAT_UNDEFINED;

        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_R8G8B8A8_UNORM ||
                availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
            {
                if (returnFormat.format != VK_FORMAT_R8G8B8A8_UINT)
                {
                    returnFormat = availableFormat;
                }
            }
        }

        if (returnFormat.format == VK_FORMAT_UNDEFINED)
        {
            _logger.logWarningLine(
                "Vulkan was unable to detect one of the preferred VkFormats for the specified surface. The first "
                "format found is now being used. This may result in unexpected behaviour.");

            returnFormat = availableFormats[0];
        }
        else
        {
            _logger.logInfo("Preferred VkFormat detected.");
        }

        return returnFormat;
    }

    // TODO: freesync and gsync support will go here in a later PR.
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this will likely need extra data in the future
    VkPresentModeKHR GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::ChooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& /*availablePresentModes*/) const noexcept
    {
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::ChooseSwapExtent(
        const VkSurfaceCapabilitiesKHR& capabilities) const noexcept
    {
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }

        auto surface = GetDevice()->GetSurface();
        auto localSize = surface->GetSize();

        VkExtent2D actualExtent = {static_cast<uint32_t>(localSize.x), static_cast<uint32_t>(localSize.y)};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }

    VkSwapchainKHR GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::CreateSwapchain(VkSwapchainKHR oldSwapchain)
    {
        auto adapter = GetDevice()->GetAdapter();
        auto surfaceContext = GetDevice()->GetSurfaceContext();
        auto surface = surfaceContext->GetSurfaceContextHandle();

        auto swapChainSupport = Vulkan::Utilities::QuerySwapChainSupport(adapter->GetPhysicalDevice(),
                                                                         surfaceContext->GetSurfaceContextHandle());

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount +
                              1; // this variable gets re-used for the actual image count later

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        auto indices = Vulkan::Utilities::FindQueueFamilies(adapter->GetPhysicalDevice(), surface);
        std::array<uint32_t, 2> queueFamilyIndices{indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = oldSwapchain;

        VkSwapchainKHR vulkanSwapchain = VK_NULL_HANDLE;
        VkResult swapChainResult =
            vkCreateSwapchainKHR(GetDevice()->GetVulkanDevice(), &createInfo, nullptr, &vulkanSwapchain);
        if (swapChainResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkSwapchainKHR.", swapChainResult);
        }

        if (oldSwapchain != VK_NULL_HANDLE)
        {
            vkDestroySwapchainKHR(GetDevice()->GetVulkanDevice(), oldSwapchain, nullptr);
        }

        _vulkanSwapchainFormat = surfaceFormat.format;
        _swapchainExtent = extent;

        _logger.logInfoLine("VkSwapchainKHR successfully created.");
        return vulkanSwapchain;
    }

    // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<
        Vulkan::VulkanGraphicsBackend>::shared_from_this()
    {
        return std::static_pointer_cast<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>>(
            GraphicsDeviceObject::shared_from_this());
    }

    GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::GraphicsSwapchain(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice)
        : _device(std::move(graphicsDevice)),
          _swapchain(VK_NULL_HANDLE),
          _currentImageIndex(0ULL),
          _logger(Logging::CONSOLE_LOG_GFX),
          _vulkanSwapchainFormat(VK_FORMAT_UNDEFINED),
          _swapchainExtent{}
    {
        CreateSwapchain();
    }

    GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::~GraphicsSwapchain() noexcept
    {
        if (_swapchain != VK_NULL_HANDLE)
        {
            vkDestroySwapchainKHR(GetDevice()->GetVulkanDevice(), _swapchain, nullptr);
        }
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<
        Vulkan::VulkanGraphicsBackend>::GetDevice() const
    {
        return _device;
    }

    std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<
        Vulkan::VulkanGraphicsBackend>::AcquireNextImage()
    {
        const VkResult acquireNextImageResult = vkAcquireNextImageKHR(
            GetDevice()->GetVulkanDevice(), _swapchain, std::numeric_limits<uint64_t>::max(), VK_NULL_HANDLE,
            GetDevice()->GetPresentCompletionFence()->GetVulkanFence(), &_currentImageIndex);

        if (acquireNextImageResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to acquire next VkImage! Reason: " +
                                     std::to_string(acquireNextImageResult));
        }

        return nullptr;
    }

    bool GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::Present()
    {
        auto presentCompletionGraphicsFence = GetDevice()->GetPresentCompletionFence();
        presentCompletionGraphicsFence->Wait();
        presentCompletionGraphicsFence->Reset();

        auto currentImageIndex = _currentImageIndex;
        VkSwapchainKHR vulkanSwapchain = _swapchain;

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &vulkanSwapchain;
        presentInfo.pImageIndices = &currentImageIndex;

        auto context = _swapchainImages[_currentImageIndex];
        auto fence = context->GetFence();
        fence->Wait();
        fence->Reset();

        const VkResult presentResult = vkQueuePresentKHR(GetDevice()->GetVulkanPresentQueue(), &presentInfo);

        if (presentResult != VK_SUCCESS && presentResult != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("Failed to present the data within the present queue!");
        }
        return false;
    }

    void GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::RecreateSwapchain()
    {
        CreateSwapchain(_swapchain);
    }
}
