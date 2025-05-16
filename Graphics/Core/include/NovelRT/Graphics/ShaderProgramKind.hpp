#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class ShaderProgramKind : uint32_t
    {
        Unknown = 0,
        Vertex = 1,
        Pixel = 2,
        Fragment = Pixel
    };
}
