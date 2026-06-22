#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTree.hpp>
#include <uuid.h>

namespace NovelRT::Ecs::Scripting::Components
{
    struct LoadedDecisionTree
    {
        uuids::uuid assetId{};
        std::shared_ptr<NovelRT::Scripting::DecisionTree>* decisionTree;

        inline LoadedDecisionTree& operator+=(const LoadedDecisionTree& other)
        {
            if (decisionTree != nullptr)
            {
                delete decisionTree;
            }

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const LoadedDecisionTree& other) const noexcept
        {
            return assetId == other.assetId && decisionTree == other.decisionTree;
        }
    };
}
