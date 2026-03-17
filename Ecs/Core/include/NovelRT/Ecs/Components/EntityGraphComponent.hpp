#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>

#include <limits>

namespace NovelRT::Ecs::Components
{
    struct EntityGraphComponent
    {
        bool isValid = true;
        EntityId parent = std::numeric_limits<EntityId>::max();
        EntityId childrenStartNode = std::numeric_limits<EntityId>::max();

        inline EntityGraphComponent& operator+=(const EntityGraphComponent& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const EntityGraphComponent& other) const noexcept
        {
            return isValid == other.isValid && parent == other.parent && childrenStartNode == other.childrenStartNode;
        }

        [[nodiscard]] inline bool operator!=(const EntityGraphComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };
}
