// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/Statuses/TriggerCue.hpp>

// clang-format off
// Lua includes operate in this order.
#include <lua.h>
#include <lauxlib.h>
// clang-format on

NovelRT::Scripting::Statuses::TriggerCue::TriggerCue(const DecisionTreeCue* cue,
                                                     lua_State* L,
                                                     const std::shared_ptr<ScriptManager>& manager)
    : DecisionTreeStatus(L, std::move(manager)),
      _cue(cue)
{
}

auto NovelRT::Scripting::Statuses::TriggerCue::GetCue() const -> const DecisionTreeCue*
{
    return _cue;
}


auto NovelRT::Scripting::Statuses::TriggerCue::Continue() -> std::unique_ptr<DecisionTreeStatus>
{
    return DoContinue(0);
}
