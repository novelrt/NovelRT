// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>

#include <format>

// clang-format off
// Lua includes operate in this order.
#include <lua.h>
#include <lauxlib.h>
// clang-format on

NovelRT::Scripting::Statuses::Branch::Branch(const std::string& prompt,
                                             const std::vector<std::string>& options,
                                             lua_State* L,
                                             const std::shared_ptr<ScriptManager>& manager)
    : DecisionTreeStatus(L, std::move(manager)), _prompt(prompt), _options(std::move(options))
{
}

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
        throw NovelRT::Exceptions::InvalidOperationException(
            std::format("Index {} was outside the range of the array", index));

    lua_pushinteger(_state, static_cast<lua_Integer>(index));
    return DoContinue(1);
}
