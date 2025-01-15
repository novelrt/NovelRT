#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsResourceAccess : uint32_t
    {
        None = 1 << 0,
        Read = 1 << 1,
        Write = 1 << 2,
        ReadWrite = Read | Write,
    };
}
