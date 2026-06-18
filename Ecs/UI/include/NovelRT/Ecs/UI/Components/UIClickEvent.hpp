#pragma once

#include <cstdint>
#include <limits>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::UI::Components
{
    struct UIClickEvent
    {
        uint64_t eventId = std::numeric_limits<uint64_t>::max();

        inline UIClickEvent& operator+=(const UIClickEvent& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const UIClickEvent& other) const noexcept
        {
            return eventId == other.eventId;
        }
    };
}