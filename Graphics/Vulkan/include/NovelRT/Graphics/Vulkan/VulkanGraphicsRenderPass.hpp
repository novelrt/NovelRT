#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
#include <memory>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    struct GraphicsRenderPassDescription;

    template<>
    class GraphicsRenderPass<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        VkRenderPass _vulkanRenderPass;

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        explicit GraphicsRenderPass(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
                                    const GraphicsRenderPassDescription& description);
        ~GraphicsRenderPass() noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;

        [[nodiscard]] VkRenderPass GetVulkanRenderPass() const noexcept;
    };
}
