// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_NETAL_UTILITIES_PIPELINEBLENDFACTOR_H
#define NOVELRT_GRAPHICS_METAL_UTILITIES_PIPELINEBLENDFACTOR_H

#ifndef NOVELRT_GRAPHICS_METAL_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Metal.Utilities.h instead for the Graphics::Metal::Utilities namespace subset.
#endif

// TODO: Once Metal has been added as a dependency and we have access to the blend enum Metal_BLEND remove magic numbers
// and uncomment the returns with the enums.
namespace NovelRT::Graphics::Metal::Utilities
{
    [[nodiscard]] inline VkBlendFactor GetMetalBlendFactor(GraphicsPipelineBlendFactor blendFactor)
    {
        switch (blendFactor)
        {
            case GraphicsPipelineBlendFactor::Zero:
                // return MTLBlendFactor.zero;
                return 0;
                break;
            case GraphicsPipelineBlendFactor::One:
                // return MTLBlendFactor.one;
                return 1;
                break;
            case GraphicsPipelineBlendFactor::SrcColour:
                // return MTLBlendFactor.sourceColor;
                return 2;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrcColour:
                // return MTLBlendFactor.oneMinusSourceColor;
                return 3;
                break;
            case GraphicsPipelineBlendFactor::DstColour:
                // return MTLBlendFactor.destinationColor;
                return 6;
                break;
            case GraphicsPipelineBlendFactor::OneMinusDstColour:
                // return MTLBlendFactor.oneMinusDestinationColor;
                return 7;
                break;
            case GraphicsPipelineBlendFactor::SrcAlpha:
                // return MTLBlendFactor.sourceAlpha;
                return 4;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrcAlpha:
                // return MTLBlendFactor.oneMinusSourceAlpha;
                return 5;
                break;
            case GraphicsPipelineBlendFactor::DstAlpha:
                // return MTLBlendFactor.destinationAlpha;
                return 8;
                break;
            case GraphicsPipelineBlendFactor::OneMinusDstAlpha:
                // return MTLBlendFactor.oneMinusDestinationAlpha;
                return 9;
                break;
            case GraphicsPipelineBlendFactor::ConstantColour:
                // return MTLBlendFactor.blendColor;
                return 11;
                break;
            case GraphicsPipelineBlendFactor::OneMinusConstantColour:
                // return MTLBlendFactor.oneMinusBlendColor;
                return 12;
                break;
            case GraphicsPipelineBlendFactor::ConstantAlpha:
                // return MTLBlendFactor.blendAlpha;
                return 13;
                break;
            case GraphicsPipelineBlendFactor::OneMinusConstantAlpha:
                // return MTLBlendFactor.oneMinusBlendAlpha;
                return 14;
                break;
            case GraphicsPipelineBlendFactor::SrcAlphaSaturate:
                // return MTLBlendFactor.sourceAlphaSaturated;
                return 10;
                break;
            case GraphicsPipelineBlendFactor::Src1Colour:
                // return MTLBlendFactor.source1Color;
                return 15;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrc1Colour:
                //  return MTLBlendFactor.oneMinusSource1Color;
                return 16;
                break;
            case GraphicsPipelineBlendFactor::Src1Alpha:
                // return MTLBlendFactor.source1Alpha;
                return 17;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrc1Alpha:
                // return MTLBlendFactor.oneMinusSource1Alpha;
                return 18;
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "The specified blend factor is not supported on the default Metal pipeline.");
        }
    }
}

#endif // !NOVELRT_GRAPHICS_METAL_UTILITIES_PIPELINEBLENDFACTOR_H
