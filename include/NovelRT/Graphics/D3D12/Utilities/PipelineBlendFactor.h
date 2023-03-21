// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_D3D12_UTILITIES_PIPELINEBLENDFACTOR_H
#define NOVELRT_GRAPHICS_D3D12_UTILITIES_PIPELINEBLENDFACTOR_H

#ifdef WIN32

#ifndef NOVELRT_GRAPHICS_D3D12_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.D3D12.Utilities.h instead for the Graphics::D3D12::Utilities namespace subset.
#endif

namespace NovelRT::Graphics::D3D12::Utilities
{
    static const D3D12_BLEND NovelRTToD3D12Blend[] = {
        D3D12_BLEND_ZERO,               // Zero = 0,
        D3D12_BLEND_ONE,                // One = 1,
        D3D12_BLEND_SRC_COLOR,          // SrcColout = 2,
        D3D12_BLEND_INV_SRC_COLOR,      // OneMinusSrcColour = 3,
        D3D12_BLEND_DEST_COLOR,         // DstColour = 4,
        D3D12_BLEND_INV_DEST_COLOR,     // OneMinusDstColour = 5,
        D3D12_BLEND_SRC_ALPHA,          // SrcAlpha = 6,
        D3D12_BLEND_INV_SRC_ALPHA,      // OneMinusSrcAlpha = 7,
        D3D12_BLEND_DEST_ALPHA,         // DstAlpha = 8,
        D3D12_BLEND_INV_DEST_ALPHA,     // OneMinusDstAlpha = 9,
        D3D12_BLEND_BLEND_FACTOR,       // ConstantColour = 10,
        D3D12_BLEND_INV_BLEND_FACTOR,   // OneMinusConstantColour = 11,
        D3D12_BLEND_ALPHA_FACTOR,       // ConstantAlpha = 12,
        D3D12_BLEND_INV_ALPHA_FACTOR,   // OneMinusConstantAlpha = 13,
        D3D12_BLEND_SRC_ALPHA_SAT,      // SrcAlphaSaturate = 14,
        D3D12_BLEND_SRC1_COLOR,         // Src1Colour = 15,
        D3D12_BLEND_INV_SRC1_COLOR,     // OneMinusSrc1Colour = 16,
        D3D12_BLEND_SRC1_ALPHA,         // Src1Alpha = 17,
        D3D12_BLEND_INV_SRC1_ALPHA,     // OneMinusSrc1Alpha = 18,
    };

    inline D3D12_BLEND GetD3D12BlendFactor(GraphicsPipelineBlendFactor blendFactor)
    {
        if (blendFactor >= GraphicsPipelineBlendFactor::__COUNT)
        {
            throw Exceptions::NotSupportedException(
                "The specified blend factor is not supported on the default D3D12 pipeline.");
        }
        static_assert((sizeof(NovelRTToD3D12Blend) / sizeof(D3D12_BLEND)) ==
                      static_cast<uint32_t>(GraphicsPipelineBlendFactor::__COUNT));
        return NovelRTToD3D12Blend[static_cast<uint32_t>(blendFactor)];
    }
}

#endif // WIN32

#endif // !NOVELRT_GRAPHICS_D3D12_UTILITIES_PIPELINEBLENDFACTOR_H
