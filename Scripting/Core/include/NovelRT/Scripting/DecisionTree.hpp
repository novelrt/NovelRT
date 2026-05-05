#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Scripting
{
    class DecisionTreeStatus;
    class ScriptManager;

    class DecisionTree
    {
        std::shared_ptr<ScriptManager> _manager;

        // Reference created with luaL_ref
        int _reference;

    public:
        // Assumes the decision tree function is on the top of the Lua stack!
        explicit DecisionTree(const std::shared_ptr<ScriptManager>& manager);
        ~DecisionTree();

        DecisionTree(const DecisionTree&) = delete;
        DecisionTree(DecisionTree&&) = default;

        DecisionTree& operator=(const DecisionTree&) = delete;
        DecisionTree& operator=(DecisionTree&&) = default;

        std::unique_ptr<DecisionTreeStatus> Begin();
    };
}
