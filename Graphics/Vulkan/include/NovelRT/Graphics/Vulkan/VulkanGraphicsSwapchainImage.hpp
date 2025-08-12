#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
#include <NovelRT/Utilities/ObjectPool.hpp>
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
        std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> _queueSubmissionFence;
        VkImage _image;
        VkImageView _imageView;

        uint32_t _width;
        uint32_t _height;

        Utilities::ObjectPool<GraphicsContext<Vulkan::VulkanGraphicsBackend>> _contextPool;
        tbb::mutex _contextMutex;

        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> CreateGraphicsContext();

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> shared_from_this();

        GraphicsSwapchainImage(std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> swapchain,
                               VkImage image,
                               uint32_t width,
                               uint32_t height);
        ~GraphicsSwapchainImage() noexcept final;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;
        [[nodiscard]] std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> GetSwapchain() const;
        [[nodiscard]] std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> GetQueueSubmissionFence()
            const noexcept;

        [[nodiscard]] VkImage GetVulkanImage() const noexcept;
        [[nodiscard]] VkImageView GetVulkanImageView() const noexcept;
        [[nodiscard]] uint32_t GetWidth() const noexcept;
        [[nodiscard]] uint32_t GetHeight() const noexcept;

        [[nodiscard]] Utilities::ObjectPoolRef<GraphicsContext<Vulkan::VulkanGraphicsBackend>> CreateOrGetContext();
        void SubmitQueuesFromContexts();
    };
}
