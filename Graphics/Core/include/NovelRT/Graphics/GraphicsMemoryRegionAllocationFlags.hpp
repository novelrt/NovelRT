#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsMemoryRegionAllocationFlags : uint32_t
    {
        None = 0,
        DedicatedCollection = 1 << 0,
        ExistingCollection = 1 << 1,
        WithinBudget = 1 << 2
    };
}
