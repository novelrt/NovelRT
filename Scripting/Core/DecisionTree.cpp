// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <format>

#include <lua.h>
#include <lauxlib.h>

namespace NovelRT::Scripting
{
    DecisionTree::DecisionTree(const std::shared_ptr<ScriptManager>& manager)
    : _manager(std::move(manager)),
      _reference(luaL_ref(_manager->GetLuaState(), LUA_REGISTRYINDEX))
    { }

    DecisionTree::~DecisionTree()
    {
        luaL_unref(_manager->GetLuaState(), LUA_REGISTRYINDEX, _reference);
    }

    std::unique_ptr<DecisionTreeStatus> DecisionTree::Begin()
    {
        int type = lua_rawgeti(_manager->GetLuaState(), LUA_REGISTRYINDEX, _reference);
        if (type != LUA_TFUNCTION)
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree type was not a function (was {})", type));

        // It's easier to just pop and re-fetch from the registry
        lua_pop(_manager->GetLuaState(), 1);
        lua_State* L = lua_newthread(_manager->GetLuaState());
        lua_rawgeti(L, LUA_REGISTRYINDEX, _reference);

        int nresults;
        int status = lua_resume(L, _manager->GetLuaState(), 0, &nresults);
        if (status != LUA_YIELD)
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield (returned {})", status));
        if (nresults != 1)
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield any results (returned {} results)", nresults));

        void* data = lua_touserdata(L, -1);
        if (data == nullptr)
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield a status (returned {})", lua_typename(L, lua_type(L, -1))));


        return std::unique_ptr<DecisionTreeStatus>(static_cast<DecisionTreeStatus*>(data));
    }
}
