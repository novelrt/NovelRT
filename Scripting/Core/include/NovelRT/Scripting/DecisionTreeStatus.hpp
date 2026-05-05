#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

typedef struct lua_State lua_State;

namespace NovelRT::Scripting
{
    class ScriptManager;

    class DecisionTreeStatus
    {
    protected:
        lua_State* _state;
        std::shared_ptr<ScriptManager> _manager;

    public:
        explicit DecisionTreeStatus(lua_State* L, const std::shared_ptr<ScriptManager>& manager);
        virtual ~DecisionTreeStatus() = default;

        DecisionTreeStatus(const DecisionTreeStatus&) = delete;
        DecisionTreeStatus(DecisionTreeStatus&&) = default;

        DecisionTreeStatus& operator=(const DecisionTreeStatus&) = delete;
        DecisionTreeStatus& operator=(DecisionTreeStatus&&) = default;
    };
}
