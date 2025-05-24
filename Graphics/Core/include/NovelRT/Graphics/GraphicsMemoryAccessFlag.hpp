#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsMemoryAccessFlag : uint32_t
    {
        None = 0,
        IndexRead = 2,
        VertexAttributeRead = 4,
        TransferRead = 2048,
        TransferWrite = 4096
    };
}
