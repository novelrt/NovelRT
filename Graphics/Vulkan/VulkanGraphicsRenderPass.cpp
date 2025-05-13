// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsRenderPass::VulkanGraphicsRenderPass(VkRenderPass renderPass) noexcept : _vulkanRenderPass(renderPass)
    {
    }

    VkRenderPass VulkanGraphicsRenderPass::GetVulkanRenderPass() const noexcept
    {
        return _vulkanRenderPass;
    }
}