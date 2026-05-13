// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <format>

#include <lua.h>
#include <lauxlib.h>

NovelRT::Scripting::DecisionTreeStatus::DecisionTreeStatus(lua_State* L, const std::shared_ptr<ScriptManager>& manager)
    : _state(L),
      _manager(std::move(manager))
{ }

auto NovelRT::Scripting::DecisionTreeStatus::DoContinue(int nargs) -> std::unique_ptr<DecisionTreeStatus>
{
    int nresults;
    int status = lua_resume(_state, _manager->GetLuaState(), nargs, &nresults);

    // A result of LUA_OK means the script wished to terminate
    if (status == LUA_OK)
        return nullptr;

    // Any result that wasn't a yield is an error state
    if (status != LUA_YIELD)
    {
        // Lua allows pushing non-string errors, so we check first.
        if (!lua_isstring(_state, -1))
        {
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield (returned {})", status));
        }

        size_t length;
        const char* msg = luaL_tolstring(_state, -1, &length);
        throw NovelRT::Exceptions::InvalidOperationException(std::string(msg, length));
    }

    // Now that we're for sure a yield state, we need to make sure it did actually return a status.
    if (nresults != 1)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield any results (returned {} results)", nresults));

    DecisionTreeStatus* data = static_cast<DecisionTreeStatus*>(lua_touserdata(_state, -1));
    if (data == nullptr)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield a status (returned {})",
                                                                         lua_typename(_state, lua_type(_state, -1))));

    return std::unique_ptr<DecisionTreeStatus>(data);
}
