#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>

#include <limits>

namespace NovelRT::Ecs::Components
{
    struct LinkedEntityListNodeComponent
    {
        bool IsValid = true;
        EntityId previous = std::numeric_limits<EntityId>::max();
        EntityId next = std::numeric_limits<EntityId>::max();

        inline LinkedEntityListNodeComponent& operator+=(const LinkedEntityListNodeComponent& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const LinkedEntityListNodeComponent& other) const noexcept
        {
            return IsValid == other.IsValid && previous == other.previous && next == other.next;
        }

        [[nodiscard]] inline bool operator!=(const LinkedEntityListNodeComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };
}
