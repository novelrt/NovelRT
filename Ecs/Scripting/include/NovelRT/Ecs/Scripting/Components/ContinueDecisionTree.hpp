#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <string>

namespace NovelRT::Ecs::Scripting::Components
{
    struct ContinueDecisionTree
    {
        bool canContinue = true;

        inline ContinueDecisionTree& operator+=(const ContinueDecisionTree& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const ContinueDecisionTree& other) const noexcept
        {
            return canContinue == other.canContinue;
        }
    };
}
