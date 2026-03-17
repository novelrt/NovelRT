#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsSemaphore.hpp>
#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <memory>
#include <oneapi/tbb/mutex.h>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> _swapchain;
        VkImage _image;
        VkImageView _imageView;

        uint32_t _width;
        uint32_t _height;

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> shared_from_this();

        GraphicsSwapchainImage(std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> swapchain,
                               VkImage image,
                               VkFormat imageFormat,
                               uint32_t width,
                               uint32_t height);
        ~GraphicsSwapchainImage() noexcept final;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;
        [[nodiscard]] std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> GetSwapchain() const;

        [[nodiscard]] VkImage GetVulkanImage() const noexcept;
        [[nodiscard]] VkImageView GetVulkanImageView() const noexcept;
        [[nodiscard]] uint32_t GetWidth() const noexcept;
        [[nodiscard]] uint32_t GetHeight() const noexcept;

        void QueueSubmit(std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList);
        void QueueSubmit(
            std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToWait,
            std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList);
        void QueueSubmit(
            std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList,
            std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToSignal);
        void QueueSubmit(
            std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToWait,
            std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList,
            std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToSignal);

        void QueueSubmit(
            NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists);
        void QueueSubmit(
            NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>,
                                               uint64_t>> semaphoresToWait,
            NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists);
        void QueueSubmit(
            NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists,
            NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>,
                                               uint64_t>> semaphoresToSignal);
        void QueueSubmit(
            NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>,
                                               uint64_t>> semaphoresToWait,
            NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists,
            NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>,
                                               uint64_t>> semaphoresToSignal);
    };
}
