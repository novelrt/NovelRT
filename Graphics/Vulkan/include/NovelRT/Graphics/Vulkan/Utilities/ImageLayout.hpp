#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsRenderPassDescription.hpp>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace NovelRT::Graphics::Vulkan
{
    [[nodiscard]] inline VkImageLayout GetVulkanImageLayout(Graphics::ImageLayout layout)
    {
        VkImageLayout returnLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        switch (layout)
        {
            case ImageLayout::Undefined:
                returnLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                break;
            case ImageLayout::General:
                returnLayout = VK_IMAGE_LAYOUT_GENERAL;
                break;
            case ImageLayout::Present:
                returnLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
                break;
            case ImageLayout::SrcTransfer:
                returnLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
                break;
            case ImageLayout::DstTransfer:
                returnLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
                break;
            case ImageLayout::ShaderReadOnlyOptimal:
                returnLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                break;
        }

        return returnLayout;
    }
}
