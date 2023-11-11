#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsPipelineInputElementKind : uint32_t
    {
        Unknown = 0,
        Position = 1,
        Colour = 2,
        Normal = 3,
        TextureCoordinate = 4
    };
}
