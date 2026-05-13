// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>

#include <format>

#include <lua.h>
#include <lauxlib.h>

NovelRT::Scripting::Statuses::Branch::Branch(const std::string& prompt,
                                             const std::vector<std::string>& options,
                                             lua_State* L,
                                             const std::shared_ptr<ScriptManager>& manager)
    : DecisionTreeStatus(L, std::move(manager)),
    _prompt(prompt),
    _options(std::move(options))
{ }

const std::string NovelRT::Scripting::Statuses::Branch::GetPrompt() const
{
    return _prompt;
}

std::span<const std::string> NovelRT::Scripting::Statuses::Branch::GetOptions() const
{
    return _options;
}

auto NovelRT::Scripting::Statuses::Branch::Continue(size_t index) -> std::unique_ptr<DecisionTreeStatus>
{
    if (_options.size() <= index)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Index {} was outside the range of the array", index));

    lua_pushinteger(_state, index);

    // TODO: it may be worth extracting this into a common logic snippet somewhere...
    int nresults;
    int status = lua_resume(_state, _manager->GetLuaState(), 1, &nresults);
    if (status == LUA_OK)
        return nullptr;

    if (status != LUA_YIELD)
    {
        if (!lua_isstring(_state, -1))
        {
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield (returned {})", status));
        }

        size_t length;
        const char* msg = luaL_tolstring(_state, -1, &length);
        throw NovelRT::Exceptions::InvalidOperationException(std::string(msg, length));
    }

    if (nresults != 1)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield any results (returned {} results)", nresults));

    void* data = lua_touserdata(_state, -1);
    if (data == nullptr)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield a status (returned {})",
                                                                         lua_typename(_state, lua_type(_state, -1))));

    return std::unique_ptr<DecisionTreeStatus>(static_cast<DecisionTreeStatus*>(data));
}
