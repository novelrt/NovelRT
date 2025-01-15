#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsBufferKind : uint32_t
    {
        Default = 0,
        Vertex = 1,
        Index = 2,
        Constant = 3,
        Uniform = Constant
    };
}
