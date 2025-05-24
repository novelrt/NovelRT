#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsPipelineStageFlag.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkPipelineStageFlags GetVulkanPipelineStageFlags(Graphics::GraphicsPipelineStageFlag stageFlag) noexcept
    {
        VkPipelineStageFlags stageFlags = VK_PIPELINE_STAGE_NONE;

        if ((stageFlag & Graphics::GraphicsPipelineStageFlag::VertexInput) == Graphics::GraphicsPipelineStageFlag::VertexInput)
        {
            stageFlags |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
        }

        if ((stageFlag & Graphics::GraphicsPipelineStageFlag::Transfer) == Graphics::GraphicsPipelineStageFlag::Transfer)
        {
            stageFlags |= VK_PIPELINE_STAGE_TRANSFER_BIT;
        }

        return stageFlags;
    }
}
