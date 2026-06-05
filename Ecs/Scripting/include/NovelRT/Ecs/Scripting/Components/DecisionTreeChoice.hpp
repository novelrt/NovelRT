#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::Scripting::Components
{
    struct DecisionTreeChoice
    {
        size_t choiceIndex;

        inline DecisionTreeChoice& operator+=(const DecisionTreeChoice& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const DecisionTreeChoice& other) const noexcept
        {
            return choiceIndex == other.choiceIndex;
        }
    };
}
