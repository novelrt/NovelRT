#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsSemaphore.hpp>
#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <deque>
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
        std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> _fence;
        Utilities::Lazy<VkSwapchainKHR> _swapchain;
        std::vector<std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>> _swapchainImages;
        std::vector<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>> _activeSemaphores;
        std::deque<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>> _semaphores;
        uint32_t _currentImageIndex;
        Logging::LoggingService _logger;
        VkFormat _vulkanSwapchainFormat;
        VkExtent2D _swapchainExtent;

        [[nodiscard]] VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;

        [[nodiscard]] VkPresentModeKHR ChooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
        [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept;

        VkSwapchainKHR CreateSwapchain(VkSwapchainKHR oldSwapchain);
        void GetSwapchainImages(VkSwapchainKHR swapchain, VkFormat swapchainFormat);

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> shared_from_this();

        GraphicsSwapchain(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice);
        ~GraphicsSwapchain() noexcept final;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;

        [[nodiscard]] VkFormat GetVulkanFormat() const;

        [[nodiscard]] std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>> GetActiveSemaphore(std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> image) const;

        [[nodiscard]] std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> AcquireNextImage();
        [[nodiscard]] bool Present();

        void RecreateSwapchain();
    };
}
