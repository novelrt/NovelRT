#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsTextureKind : uint32_t
    {
        Unknown = 0,
        OneDimensional = 1,
        TwoDimensional = 2,
        ThreeDimensional = 3
    };
}
