#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsRenderPass.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{

    template<>
    class GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>
        : public std::enable_shared_from_this<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        VkRenderPass _vulkanRenderPass;

    public:
        explicit GraphicsRenderPass(VkRenderPass VkRenderPass) noexcept;

        [[nodiscard]] VkRenderPass GetVulkanRenderPass() const noexcept;
    };
}
