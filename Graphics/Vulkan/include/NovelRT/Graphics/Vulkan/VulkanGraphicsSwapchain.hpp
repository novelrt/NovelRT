#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <vector>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsSwapchain<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        VkSwapchainKHR _swapchain;
        std::vector<std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>> _swapchainImages;
        uint32_t _currentImageIndex;
        Logging::LoggingService _logger;
        VkFormat _vulkanSwapchainFormat;
        VkExtent2D _swapchainExtent;

        [[nodiscard]] VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;

        [[nodiscard]] VkPresentModeKHR ChooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
        [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept;

        VkSwapchainKHR CreateSwapchain(VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE);
        void GetSwapchainImages();

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> shared_from_this();

        GraphicsSwapchain(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice);
        ~GraphicsSwapchain() noexcept final;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;

        [[nodiscard]] VkFormat GetVulkanFormat() const;

        [[nodiscard]] std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> AcquireNextImage();
        [[nodiscard]] bool Present();
        void RecreateSwapchain();
    };
}
