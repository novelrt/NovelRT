#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class ShaderProgramVisibility : uint32_t
    {
        NoneOrUnknown = 0,
        Vertex = 1 << 0,
        Pixel = 1 << 1,
        Fragment = Pixel,
        All = Vertex | Pixel
    };
}
