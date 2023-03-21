// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_UTILITIES_PIPELINEBLENDFACTOR_H
#define NOVELRT_GRAPHICS_VULKAN_UTILITIES_PIPELINEBLENDFACTOR_H

#ifndef NOVELRT_GRAPHICS_VULKAN_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.Utilities.h instead for the Graphics::Vulkan::Utilities namespace subset.
#endif

namespace NovelRT::Graphics::Vulkan::Utilities
{
    static const VkBlendFactor NovelRTToVulkanBlend[] = {
        VK_BLEND_FACTOR_ZERO,                     // Zero = 0,
        VK_BLEND_FACTOR_ONE,                      // One = 1,
        VK_BLEND_FACTOR_SRC_COLOR,                // SrcColout = 2,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,      // OneMinusSrcColour = 3,
        VK_BLEND_FACTOR_DST_COLOR,                // DstColour = 4,
        VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,      // OneMinusDstColour = 5,
        VK_BLEND_FACTOR_SRC_ALPHA,                // SrcAlpha = 6,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,      // OneMinusSrcAlpha = 7,
        VK_BLEND_FACTOR_DST_ALPHA,                // DstAlpha = 8,
        VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,      // OneMinusDstAlpha = 9,
        VK_BLEND_FACTOR_CONSTANT_COLOR,           // ConstantColour = 10,
        VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR, // OneMinusConstantColour = 11,
        VK_BLEND_FACTOR_CONSTANT_ALPHA,           // ConstantAlpha = 12,
        VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA, // OneMinusConstantAlpha = 13,
        VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,       // SrcAlphaSaturate = 14,
        VK_BLEND_FACTOR_SRC1_COLOR,               // Src1Colour = 15,
        VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,     // OneMinusSrc1Colour = 16,
        VK_BLEND_FACTOR_SRC1_ALPHA,               // Src1Alpha = 17,
        VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,     // OneMinusSrc1Alpha = 18,
    };

    inline VkBlendFactor GetVulkanBlendFactor(GraphicsPipelineBlendFactor blendFactor)
    {
        if (blendFactor >= GraphicsPipelineBlendFactor::__COUNT)
        {
            throw Exceptions::NotSupportedException(
                "The specified blend factor is not supported on the default Metal pipeline.");
        }
        static_assert((sizeof(NovelRTToVulkanBlend) / sizeof(VkBlendFactor)) ==
                      static_cast<uint32_t>(GraphicsPipelineBlendFactor::__COUNT));
        return NovelRTToVulkanBlend[static_cast<uint32_t>(blendFactor)];
    }
}

#endif // !NOVELRT_GRAPHICS_VULKAN_UTILITIES_PIPELINEBLENDFACTOR_H
