#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>

namespace NovelRT::Ecs
{
    struct EntityHandle
    {
        EntityId Id;
        size_t Generation;

        [[nodiscard]] bool operator==(const EntityHandle& other) const noexcept
        {
            return Id == other.Id && Generation == other.Generation;
        }
    };
}
