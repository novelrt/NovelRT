// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_METAL_UTILITIES_PIPELINEBLENDFACTOR_H
#define NOVELRT_GRAPHICS_METAL_UTILITIES_PIPELINEBLENDFACTOR_H

#ifdef TARGET_OS_MAC

#ifndef NOVELRT_GRAPHICS_METAL_UTILITIES_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Metal.Utilities.h instead for the Graphics::Metal::Utilities namespace subset.
#endif

#include <stdint.h>

namespace NovelRT::Graphics::Metal::Utilities
{
    static const MTLBlendFactor NovelRTToMetalBlend[] = {
        MTLBlendFactor.zero,                        // Zero = 0,
        MTLBlendFactor.one,                         // One = 1,
        MTLBlendFactor.sourceColor,                 // SrcColout = 2,
        MTLBlendFactor.oneMinusSourceColor,         // OneMinusSrcColour = 3,
        MTLBlendFactor.destinationColor,            // DstColour = 4,
        MTLBlendFactor.oneMinusDestinationColor,    // OneMinusDstColour = 5,
        MTLBlendFactor.sourceAlpha,                 // SrcAlpha = 6,
        MTLBlendFactor.oneMinusSourceAlpha,         // OneMinusSrcAlpha = 7,
        MTLBlendFactor.destinationAlpha,            // DstAlpha = 8,
        MTLBlendFactor.oneMinusDestinationAlpha,    // OneMinusDstAlpha = 9,
        MTLBlendFactor.blendColor,                  // ConstantColour = 10,
        MTLBlendFactor.oneMinusBlendColor,          // OneMinusConstantColour = 11,
        MTLBlendFactor.blendAlpha,                  // ConstantAlpha = 12,
        MTLBlendFactor.oneMinusBlendAlpha,          // OneMinusConstantAlpha = 13,
        MTLBlendFactor.sourceAlphaSaturated,        // SrcAlphaSaturate = 14,
        MTLBlendFactor.source1Color,                // Src1Colour = 15,
        MTLBlendFactor.oneMinusSource1Color,        // OneMinusSrc1Colour = 16,
        MTLBlendFactor.source1Alpha,                // Src1Alpha = 17,
        MTLBlendFactor.oneMinusSource1Alpha,        // OneMinusSrc1Alpha = 18,
    };

    inline MTLBlendFactor GetMetalBlendFactor(GraphicsPipelineBlendFactor blendFactor)
    {
        if (blendFactor >= __COUNT)
        {
            throw Exceptions::NotSupportedException(
                "The specified blend factor is not supported on the default Metal pipeline.");
        }
        static_assert((sizeof(NovelRTToMetalBlend) / sizeof(MTLBlendFactor)) ==
                      static_cast<uint32_t>(GraphicsPipelineBlendFactor::__COUNT));
        return NovelRTToMetalBlend[static_cast<uint32_t>(blendFactor)];
    }
}

#endif // TARGET_OS_MAC 

#endif // !NOVELRT_GRAPHICS_METAL_UTILITIES_PIPELINEBLENDFACTOR_H
