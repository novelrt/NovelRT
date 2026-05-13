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

const std::string NovelRT::Scripting::Statuses::SpokenLine::GetSpeaker() const
{
    return _speaker;
}

const std::string NovelRT::Scripting::Statuses::SpokenLine::GetText() const
{
    return _text;
}

auto NovelRT::Scripting::Statuses::SpokenLine::Continue() -> std::unique_ptr<DecisionTreeStatus>
{
    return DoContinue(0);
}
