#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;

    class VulkanGraphicsRenderPass
    {
    private:
        VkRenderPass _vulkanRenderPass;

    public:
        explicit VulkanGraphicsRenderPass(VkRenderPass VkRenderPass) noexcept;

        [[nodiscard]] VkRenderPass GetVulkanRenderPass() const noexcept;
    };
}