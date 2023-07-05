#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

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
