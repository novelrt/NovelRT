// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_TEXTUREADDRESSMODE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_TEXTUREADDRESSMODE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.Utilities.h instead for the Graphics::Vulkan::Utilities namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan::Utilities
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
                throw Exceptions::NotSupportedException("The specified texture address mode is not supported on the default Vulkan pipeline.");
                break;
        }
    }
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_TEXTUREADDRESSMODE_H
