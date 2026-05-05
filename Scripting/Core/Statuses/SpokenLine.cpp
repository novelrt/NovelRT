// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

#include <format>

#include <lua.h>
#include <lauxlib.h>

NovelRT::Scripting::Statuses::SpokenLine::SpokenLine(const std::string& speaker,
                                                     const std::string& text,
                                                     lua_State* L,
                                                     const std::shared_ptr<ScriptManager>& manager)
    : DecisionTreeStatus(L, std::move(manager)),
      _speaker(std::move(speaker)),
      _text(std::move(text))
{ }

std::string NovelRT::Scripting::Statuses::SpokenLine::GetSpeaker()
{
    return _speaker;
}

std::string NovelRT::Scripting::Statuses::SpokenLine::GetText()
{
    return _text;
}

auto NovelRT::Scripting::Statuses::SpokenLine::Continue() -> std::unique_ptr<DecisionTreeStatus>
{
    // TODO: it may be worth extracting this into a common logic snippet somewhere...
    int nresults;
    int status = lua_resume(_state, _manager->GetLuaState(), 0, &nresults);
    if (status != LUA_YIELD)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield (returned {})", status));
    if (nresults != 1)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield any results (returned {} results)", nresults));

    void* data = lua_touserdata(_state, -1);
    if (data == nullptr)
        throw NovelRT::Exceptions::InvalidOperationException(std::format("Internal error - decision tree function did not yield a status (returned {})",
                                                                         lua_typename(_state, lua_type(_state, -1))));


    return std::unique_ptr<DecisionTreeStatus>(static_cast<DecisionTreeStatus*>(data));
}
