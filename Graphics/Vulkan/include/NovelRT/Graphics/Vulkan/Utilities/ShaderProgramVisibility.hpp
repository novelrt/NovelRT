#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkShaderStageFlags GetVulkanShaderStageFlags(ShaderProgramVisibility shaderVisibility) noexcept
    {
        VkShaderStageFlags stageFlags = 0;

        if ((shaderVisibility & ShaderProgramVisibility::Vertex) == ShaderProgramVisibility::Vertex)
        {
            stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;
        }

        if ((shaderVisibility & ShaderProgramVisibility::Pixel) == ShaderProgramVisibility::Pixel)
        {
            stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        return stageFlags;
    }
}
