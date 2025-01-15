#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/TexelFormat.hpp>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkFormat Map(TexelFormat texelFormat) noexcept
    {
        VkFormat returnFormat = VK_FORMAT_R8G8B8A8_UNORM;

        switch (texelFormat)
        {
            case TexelFormat::R8G8B8A8_UNORM:
                returnFormat = VK_FORMAT_R8G8B8A8_UNORM;
                break;
            case TexelFormat::R16_SINT:
                returnFormat = VK_FORMAT_R16_SINT;
                break;
            case TexelFormat::R16G16UINT:
                returnFormat = VK_FORMAT_R16G16_UINT;
                break;
            default:
                returnFormat = VK_FORMAT_UNDEFINED;
                break;
        }

        return returnFormat;
    }
}
