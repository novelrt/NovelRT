// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/NotSupportedException.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Support.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Texel.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSemaphore.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace NovelRT::Graphics
{
    VkSurfaceFormatKHR GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::ChooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept
    {
        auto it =
            std::find_if(availableFormats.begin(), availableFormats.end(),
                         [](auto& it)
                         {
                             return it.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR &&
                                    (it.format == VK_FORMAT_R8G8B8A8_UNORM || it.format == VK_FORMAT_B8G8R8A8_UNORM);
                         });

        if (it != availableFormats.end())
        {
            return *it;
        }

        _logger.logWarningLine(
            "Vulkan was unable to detect one of the preferred VkFormats for the specified surface. The first "
            "format found is now being used. This may result in unexpected behaviour.");

        return availableFormats.at(0);
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

        GetSwapchainImages(vulkanSwapchain, surfaceFormat.format);

        return vulkanSwapchain;
    }

    void GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::GetSwapchainImages(VkSwapchainKHR swapchain,
                                                                              VkFormat swapchainFormat)
    {
        VkDevice device = GetDevice()->GetVulkanDevice();
        VkSwapchainKHR vulkanSwapchain = swapchain;

        uint32_t imageCount = 0;
        VkResult imagesKHRQuery = vkGetSwapchainImagesKHR(device, vulkanSwapchain, &imageCount, nullptr);

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        _swapchainImages.clear();
        _swapchainImages.reserve(imageCount);
        _activeSemaphores.clear();
        _activeSemaphores.resize(imageCount);
        for (size_t n = _semaphores.size(); n < imageCount * 2 + 1; n++)
        {
            _semaphores.emplace_back(GetDevice()->CreateSemaphore());
        }

        std::vector<VkImage> swapchainImages = std::vector<VkImage>(imageCount);
        imagesKHRQuery = vkGetSwapchainImagesKHR(device, vulkanSwapchain, &imageCount, swapchainImages.data());

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        for (auto&& image : swapchainImages)
        {
            _swapchainImages.push_back(std::make_shared<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>(
                shared_from_this(), image, swapchainFormat, _swapchainExtent.width, _swapchainExtent.height));
        }
    }

    // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<
        Vulkan::VulkanGraphicsBackend>::shared_from_this()
    {
        return std::static_pointer_cast<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>>(
            GraphicsDeviceObject::shared_from_this());
    }

    [[nodiscard]] Graphics::TexelFormat GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::GetFormat()
    {
        return Vulkan::Utilities::MapInverse(GetVulkanFormat());
    }

    GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::GraphicsSwapchain(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice)
        : _device(std::move(graphicsDevice)),
          _fence(std::make_shared<GraphicsFence<Vulkan::VulkanGraphicsBackend>>(_device, false)),
          _swapchain([this]() { return CreateSwapchain(VK_NULL_HANDLE); }),
          _currentImageIndex(0ULL),
          _logger(Logging::CONSOLE_LOG_GFX),
          _vulkanSwapchainFormat(VK_FORMAT_UNDEFINED),
          _swapchainExtent{}
    {
    }

    GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::~GraphicsSwapchain() noexcept
    {
        if (_swapchain.HasValue())
        {
            vkDestroySwapchainKHR(GetDevice()->GetVulkanDevice(), _swapchain.Get(), nullptr);
        }
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<
        Vulkan::VulkanGraphicsBackend>::GetDevice() const
    {
        return _device;
    }

    VkFormat GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::GetVulkanFormat() const
    {
        // Ensure the swapchain was created
        unused(_swapchain.Get());
        return _vulkanSwapchainFormat;
    }

    std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::
        GetActiveSemaphore(std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> image) const
    {
        auto index =
            std::distance(_swapchainImages.begin(), std::find(_swapchainImages.begin(), _swapchainImages.end(), image));
        return _activeSemaphores[index];
    }

    std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchain<
        Vulkan::VulkanGraphicsBackend>::AcquireNextImage()
    {
        auto semaphore = _semaphores.front();
        _semaphores.pop_front();
        const VkResult acquireNextImageResult = vkAcquireNextImageKHR(
            GetDevice()->GetVulkanDevice(), _swapchain.Get(), std::numeric_limits<uint64_t>::max(),
            semaphore->GetVulkanSemaphore(), _fence->GetVulkanFence(), &_currentImageIndex);

        if (acquireNextImageResult != VK_SUCCESS && acquireNextImageResult != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("Failed to acquire next VkImage! Reason: " +
                                     std::to_string(acquireNextImageResult));
        }

        if (_activeSemaphores[_currentImageIndex] != nullptr)
        {
            _semaphores.push_back(_activeSemaphores[_currentImageIndex]);
        }

        _activeSemaphores[_currentImageIndex] = semaphore;
        return _swapchainImages[_currentImageIndex];
    }

    bool GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::Present()
    {
        // Wait for the acquire fence to complete
        _fence->Wait();
        _fence->Reset();

        auto currentImageIndex = _currentImageIndex;
        auto image = _swapchainImages[currentImageIndex];

        VkSwapchainKHR vulkanSwapchain = _swapchain.Get();
        VkSemaphore imageSemaphore = _activeSemaphores[currentImageIndex]->GetVulkanSemaphore();

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &imageSemaphore;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &vulkanSwapchain;
        presentInfo.pImageIndices = &currentImageIndex;

        const VkResult presentResult = vkQueuePresentKHR(GetDevice()->GetVulkanPresentQueue(), &presentInfo);
        if (presentResult != VK_SUCCESS && presentResult != VK_SUBOPTIMAL_KHR)
        {
            return false;
        }

        return true;
    }

    void GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>::RecreateSwapchain()
    {
        _device->WaitForIdle();
        _swapchain.Reset(CreateSwapchain(_swapchain.HasValue() ? _swapchain.Get() : VK_NULL_HANDLE));
    }
}
