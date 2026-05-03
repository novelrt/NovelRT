#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

typedef struct lua_State lua_State;

namespace NovelRT::Scripting
{
    class DecisionTreeStatus
    {
        std::shared_ptr<ScriptManager> _manager;

        // Reference created with luaL_ref
        int _reference;

    public:
        // Assumes the coroutine is on the top of the Lua stack
        explicit DecisionTreeStatus(const std::shared_ptr<ScriptManager>& manager);
        virtual ~DecisionTreeStatus();

        DecisionTreeStatus(const DecisionTreeStatus&) = delete;
        DecisionTreeStatus(DecisionTreeStatus&&) = default;

        DecisionTreeStatus& operator=(const DecisionTreeStatus&) = delete;
        DecisionTreeStatus& operator=(DecisionTreeStatus&&) = default;

        DecisionTreeStatus* Continue();
    };
}
