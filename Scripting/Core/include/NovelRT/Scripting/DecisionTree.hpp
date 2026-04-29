#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Scripting
{
    class DecisionTreeResult;

    class DecisionTree
    {
        // Reference created with luaL_ref
        int reference;

    public:
        explicit DecisionTree();
        ~DecisionTree() = default;

        DecisionTree(const DecisionTree&) = delete;
        DecisionTree(DecisionTree&&) = default;

        DecisionTree& operator=(const DecisionTree&) = delete;
        DecisionTree& operator=(DecisionTree&&) = default;

        std::unique_ptr<DecisionTreeResult> Begin();
    };
}
