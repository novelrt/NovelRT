#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTree.hpp>
#include <uuid.h>

namespace NovelRT::Ecs::Scripting::Components
{
    struct DecisionTreeLoadRequest
    {
        uuids::uuid assetId{};

        inline DecisionTreeLoadRequest& operator+=(const DecisionTreeLoadRequest& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const DecisionTreeLoadRequest& other) const noexcept
        {
            return assetId == other.assetId;
        }
    };
}
