#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/GraphicsDeviceObject.hpp"
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
#include <memory>
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
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> _queueSubmissionFence;
        VkImage _image;
        VkImageView _imageView;

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> shared_from_this();

        GraphicsSwapchainImage(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
                               VkImage image);
        ~GraphicsSwapchainImage() noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;
        [[nodiscard]] VkImage GetImage() const noexcept;
        [[nodiscard]] VkImageView GetImageView() const noexcept;

        // TODO: FINISH THIS: std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>>
        void SubmitQueuesFromContexts();
    };
}
