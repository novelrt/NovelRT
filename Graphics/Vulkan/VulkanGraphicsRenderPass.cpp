// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsRenderPass.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsRenderPass = GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>;

    VulkanGraphicsRenderPass::GraphicsRenderPass(VkRenderPass renderPass) noexcept
        : _vulkanRenderPass(renderPass)
    {
    }

    VkRenderPass VulkanGraphicsRenderPass::GetVulkanRenderPass() const noexcept
    {
        return _vulkanRenderPass;
    }
}
