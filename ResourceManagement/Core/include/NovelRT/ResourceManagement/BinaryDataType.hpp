#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::ResourceManagement
{
    enum class BinaryDataType : uint32_t
    {
        NullOrUnknown = 0,
        Boolean = 1,
        Int32 = 2,
        Int64 = 3,
        UInt32 = 4,
        UInt64 = 5,
        Double = 6,
        String = 7,
        Binary = 8
    };
}
