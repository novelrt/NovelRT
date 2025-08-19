#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsRenderTarget;

    template<>
    class GraphicsRenderTarget<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        VkFramebuffer _framebuffer;

    public:
        GraphicsRenderTarget(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
                             Utilities::Span<VkImageView> imageViews,
                             const std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>>& renderPass,
                             uint32_t width,
                             uint32_t height);

        ~GraphicsRenderTarget() noexcept final;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const noexcept;

        [[nodiscard]] VkFramebuffer GetVulkanFramebuffer() const noexcept;
    };
}
