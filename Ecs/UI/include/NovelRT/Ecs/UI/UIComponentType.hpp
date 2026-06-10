#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Ecs::UI
{
    enum class UIComponentType : int32_t
    {
        Container = 0,
        Button = 1,
        Text = 2
    };
}
