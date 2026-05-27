#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTree.hpp>

namespace NovelRT::Ecs::Scripting::Components
{
    struct ActiveDecisionTree
    {
        std::shared_ptr<NovelRT::Scripting::DecisionTree>* decisionTree;

        inline ActiveDecisionTree& operator+=(const ActiveDecisionTree& other)
        {
            if (decisionTree != nullptr)
            {
                delete decisionTree;
            }

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const ActiveDecisionTree& other) const noexcept
        {
            return decisionTree == other.decisionTree;
        }
    };
}
