// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_D3D12_UTILITIES_PIPELINEBLENDFACTOR_H
#define NOVELRT_GRAPHICS_D3D12_UTILITIES_PIPELINEBLENDFACTOR_H

#ifndef NOVELRT_GRAPHICS_D3D12_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.D3D12.Utilities.h instead for the Graphics::D3D12::Utilities namespace subset.
#endif


// TODO: Once D3D12 has been added as a dependency and we have access to the blend enum D3D12_BLEND remove magic numbers and uncomment the returns with the enums.
namespace NovelRT::Graphics::D3D12::Utilities
{
    [[nodiscard]] inline VkBlendFactor GetD3D12BlendFactor(GraphicsPipelineBlendFactor blendFactor)
    {
        switch (blendFactor)
        {
            case GraphicsPipelineBlendFactor::Zero:
                // return D3D12_BLEND_ZERO;
                return 1;
                break;
            case GraphicsPipelineBlendFactor::One:
                // return D3D12_BLEND_ONE;
                return 2;
                break;
            case GraphicsPipelineBlendFactor::SrcColour:
                // return D3D12_BLEND_SRC_COLOR;
                return 3;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrcColour:
                // return D3D12_BLEND_INV_SRC_COLOR;
                return 4;
                break;
            case GraphicsPipelineBlendFactor::DstColour:
                // return D3D12_BLEND_DEST_COLOR;
                return 9;
                break;
            case GraphicsPipelineBlendFactor::OneMinusDstColour:
                // return D3D12_BLEND_INV_DEST_COLOR;
                return 10;
                break;
            case GraphicsPipelineBlendFactor::SrcAlpha:
                // return D3D12_BLEND_SRC_ALPHA;
                return 5;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrcAlpha:
                // return D3D12_BLEND_INV_SRC_ALPHA;
                return 6;
                break;
            case GraphicsPipelineBlendFactor::DstAlpha:
                // return D3D12_BLEND_DEST_ALPHA;
                return 7;
                break;
            case GraphicsPipelineBlendFactor::OneMinusDstAlpha:
                // return D3D12_BLEND_INV_DEST_ALPHA;
                return 8;
                break;
            case GraphicsPipelineBlendFactor::ConstantColour:
                // return D3D12_BLEND_BLEND_FACTOR;
                return 14;
                break;
            case GraphicsPipelineBlendFactor::OneMinusConstantColour:
                // return D3D12_BLEND_INV_BLEND_FACTOR;
                return 15;
                break;
            case GraphicsPipelineBlendFactor::ConstantAlpha:
                // return D3D12_BLEND_ALPHA_FACTOR;
                return 20;
                break;
            case GraphicsPipelineBlendFactor::OneMinusConstantAlpha:
                // return D3D12_BLEND_INV_ALPHA_FACTOR;
                return 21;
                break;
            case GraphicsPipelineBlendFactor::SrcAlphaSaturate:
                // return D3D12_BLEND_SRC_ALPHA_SAT;
                return 11;
                break;
            case GraphicsPipelineBlendFactor::Src1Colour:
                // return D3D12_BLEND_SRC1_COLOR;
                return 16;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrc1Colour:
                //  return D3D12_BLEND_INV_SRC1_COLOR;
                return 17;
                break;
            case GraphicsPipelineBlendFactor::Src1Alpha:
                // return D3D12_BLEND_SRC1_ALPHA;
                return 18;
                break;
            case GraphicsPipelineBlendFactor::OneMinusSrc1Alpha:
                // return D3D12_BLEND_INV_SRC1_ALPHA;
                return 19;
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "The specified blend factor is not supported on the default D3D12 pipeline.");
        }
    }
}

#endif // !NOVELRT_GRAPHICS_D3D12_UTILITIES_PIPELINEBLENDFACTOR_H
