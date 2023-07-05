#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkSamplerAddressMode GetVulkanAddressMode(GraphicsTextureAddressMode addressMode)
    {
        switch (addressMode)
        {
            case GraphicsTextureAddressMode::Wrap:
                return VK_SAMPLER_ADDRESS_MODE_REPEAT;
                break;
            case GraphicsTextureAddressMode::MirroredRepeat:
                return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
                break;
            case GraphicsTextureAddressMode::ClampToEdge:
                return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
                break;
            case GraphicsTextureAddressMode::ClampToBorder:
                return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
                break;
            case GraphicsTextureAddressMode::MirrorClampToEdge:
                return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "The specified texture address mode is not supported on the default Vulkan pipeline.");
                break;
        }
    }
}
