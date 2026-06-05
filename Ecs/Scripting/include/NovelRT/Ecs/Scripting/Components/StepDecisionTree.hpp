#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Scripting/DecisionTreeStepManager.hpp>

namespace NovelRT::Ecs::Scripting::Components
{
    struct StepDecisionTree
    {
        DecisionTreeStepKind stepKind;

        inline StepDecisionTree& operator+=(const StepDecisionTree& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const StepDecisionTree& other) const noexcept
        {
            return stepKind == other.stepKind;
        }
    };
}
