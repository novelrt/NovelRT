#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

typedef struct lua_State lua_State;

namespace NovelRT::Scripting
{
    class DecisionTree;

    class ScriptManager
    {
    private:
        struct CloseState {
            void operator()(lua_State*);
        };

        std::unique_ptr<lua_State, CloseState> _state;

    public:
        explicit ScriptManager();
        ~ScriptManager() = default;

        ScriptManager(const ScriptManager&) = delete;
        ScriptManager(ScriptManager&&) = default;

        ScriptManager& operator=(const ScriptManager&) = delete;
        ScriptManager& operator=(ScriptManager&&) = default;

        std::unique_ptr<DecisionTree> LoadDecisionTree(/* TODO: resource file */);
    };
}
