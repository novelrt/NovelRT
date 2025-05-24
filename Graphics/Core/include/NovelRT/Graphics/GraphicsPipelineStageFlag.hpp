#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsPipelineStageFlag : uint32_t
    {
        None = 0,
        VertexInput = 4,
        Transfer = 4096
    };
}
