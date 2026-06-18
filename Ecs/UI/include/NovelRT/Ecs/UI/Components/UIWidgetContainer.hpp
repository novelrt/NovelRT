#pragma once

#include <NovelRT/Ecs/EcsUtils.hpp>

#include <limits>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::UI::Components
{
    struct UIWidgetContainer
    {
        const char* title = "";
        bool closeable = false;

        inline UIWidgetContainer& operator+=(const UIWidgetContainer& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const UIWidgetContainer& other) const noexcept
        {
            return title == other.title && closeable == other.closeable; // && flags == other.flags;
        }
    };
}