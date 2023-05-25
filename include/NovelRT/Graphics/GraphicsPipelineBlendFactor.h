// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSPIPELINEBLENDFACTOR_H
#define NOVELRT_GRAPHICS_GRAPHICSPIPELINEBLENDFACTOR_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    enum class GraphicsPipelineBlendFactor : uint32_t
    {
        Zero = 0,
        One = 1,
        SrcColour = 2,
        OneMinusSrcColour = 3,
        DstColour = 4,
        OneMinusDstColour = 5,
        SrcAlpha = 6,
        OneMinusSrcAlpha = 7,
        DstAlpha = 8,
        OneMinusDstAlpha = 9,
        ConstantColour = 10,
        OneMinusConstantColour = 11,
        ConstantAlpha = 12,
        OneMinusConstantAlpha = 13,
        SrcAlphaSaturate = 14,
        Src1Colour = 15,
        OneMinusSrc1Colour = 16,
        Src1Alpha = 17,
        OneMinusSrc1Alpha = 18,
        __COUNT
    };
}

#endif // NOVELRT_GRAPHICS_GRAPHICSPIPELINEBLENDFACTOR_H
