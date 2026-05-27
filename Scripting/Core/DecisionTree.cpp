// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <format>

// clang-format off
// Lua includes operate in this order.
#include <lua.h>
#include <lauxlib.h>
// clang-format on

namespace NovelRT::Scripting
{
    DecisionTree::DecisionTree(const std::shared_ptr<ScriptManager>& manager)
        : _manager(std::move(manager)), _reference(luaL_ref(_manager->GetLuaState(), LUA_REGISTRYINDEX))
    {
    }

    DecisionTree::~DecisionTree()
    {
        luaL_unref(_manager->GetLuaState(), LUA_REGISTRYINDEX, _reference);
    }

    std::unique_ptr<DecisionTreeStatus> DecisionTree::Begin()
    {
        int type = lua_rawgeti(_manager->GetLuaState(), LUA_REGISTRYINDEX, _reference);
        if (type != LUA_TFUNCTION)
            throw NovelRT::Exceptions::InvalidOperationException(
                std::format("Internal error - decision tree type was not a function (was {})", type));

        // It's easier to just pop and re-fetch from the registry
        lua_pop(_manager->GetLuaState(), 1);
        lua_State* L = lua_newthread(_manager->GetLuaState());
        lua_rawgeti(L, LUA_REGISTRYINDEX, _reference);

        int nresults;
        int status = lua_resume(L, _manager->GetLuaState(), 0, &nresults);

        // When starting a decision tree, it's not valid for it to immediately terminate.
        // Otherwise, the remainder of this logic is equivalent to DecisionTreeStatus::DoContinue
        if (status != LUA_YIELD)
        {
            if (!lua_isstring(L, -1))
            {
                throw NovelRT::Exceptions::InvalidOperationException(
                    std::format("Internal error - decision tree function did not yield (returned {})", status));
            }

            size_t length;
            const char* msg = luaL_tolstring(L, -1, &length);
            throw NovelRT::Exceptions::InvalidOperationException(std::string(msg, length));
        }

        if (nresults != 1)
            throw NovelRT::Exceptions::InvalidOperationException(std::format(
                "Internal error - decision tree function did not yield any results (returned {} results)", nresults));

        DecisionTreeStatus* data = static_cast<DecisionTreeStatus*>(lua_touserdata(L, -1));
        if (data == nullptr)
            throw NovelRT::Exceptions::InvalidOperationException(
                std::format("Internal error - decision tree function did not yield a status (returned {})",
                            lua_typename(L, lua_type(L, -1))));

        return std::unique_ptr<DecisionTreeStatus>(data);
    }
}
