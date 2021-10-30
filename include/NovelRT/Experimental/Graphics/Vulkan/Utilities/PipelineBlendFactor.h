// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_PIPELINEBLENDFACTOR_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_PIPELINEBLENDFACTOR_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.Utilities.h instead for the Graphics::Vulkan::Utilities namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkBlendFactor GetVulkanBlendFactor(GraphicsPipelineBlendFactor blendFactor)
    {
        switch (blendFactor)
        {
            case GraphicsPipelineBlendFactor::Zero:
                return VK_BLEND_FACTOR_ZERO;
                break;
            case GraphicsPipelineBlendFactor::One:
                return VK_BLEND_FACTOR_ONE;
                break;
            case GraphicsPipelineBlendFactor::SrcColour:
                return VK_BLEND_FACTOR_SRC_COLOR;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrcColour:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
                break;
            case GraphicsPipelineBlendFactor::DstColour:
                return VK_BLEND_FACTOR_DST_COLOR;
                break;
            case GraphicsPipelineBlendFactor::OneMinusDstColour:
                return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
                break;
            case GraphicsPipelineBlendFactor::SrcAlpha:
                return VK_BLEND_FACTOR_SRC_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrcAlpha:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::DstAlpha:
                return VK_BLEND_FACTOR_DST_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::OneMinusDstAlpha:
                return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::ConstantColour:
                return VK_BLEND_FACTOR_CONSTANT_COLOR;
                break;
            case GraphicsPipelineBlendFactor::OneMinusConstantColour:
                return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
                break;
            case GraphicsPipelineBlendFactor::ConstantAlpha:
                return VK_BLEND_FACTOR_CONSTANT_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::OneMinusConstantAlpha:
                return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::SrcAlphaSaturate:
                return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
                break;
            case GraphicsPipelineBlendFactor::Src1Colour:
                return VK_BLEND_FACTOR_SRC1_COLOR;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrc1Colour:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
                break;
            case GraphicsPipelineBlendFactor::Src1Alpha:
                return VK_BLEND_FACTOR_SRC1_ALPHA;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrc1Alpha:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
                break;
            default:
                throw Exceptions::NotSupportedException("The specified blend factor is not supported on the default Vulkan pipeline.");
        }
    }
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_UTILITIES_PIPELINEBLENDFACTOR_H
