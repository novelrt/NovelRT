// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/Statuses/Branch.hpp>

#include "../Bindings.hpp"

#include <algorithm>
#include <format>

struct ChoiceInfo
{
    std::string prompt;
};

int CreateChoice(lua_State* L)
{
    const char* prompt = luaL_checkstring(L, 1);
    void* buffer = lua_newuserdatauv(L, sizeof(ChoiceInfo), 0);
    luaL_setmetatable(L, "Choice");

    // Because we're creating objects in memory we don't own, we need to use placement new.
    new (buffer) ChoiceInfo{prompt};

    return 1;
}

int CleanupChoice(lua_State* L)
{
    ChoiceInfo* it = static_cast<ChoiceInfo*>(luaL_checkudata(L, 1, "Choice"));
    // Because we're using placement new, we need to manually call the destructor to ensure it gets cleaned up.
    it->~ChoiceInfo();
    return 0;
}

int ProduceChoices_Cont(lua_State* L, int, lua_KContext)
{
    auto choice = luaL_checkinteger(L, -1);
    lua_pushinteger(L, choice + 1);
    return 1;
}

int ProduceChoices(lua_State* L)
{
    ChoiceInfo* it = static_cast<ChoiceInfo*>(luaL_checkudata(L, 1, "Choice"));
    luaL_checktype(L, 2, LUA_TTABLE);
    std::vector<std::string> choices(lua_rawlen(L, 2));
    for (size_t n = 0; n < choices.size(); n++)
    {
        int type = lua_rawgeti(
            L, 2, static_cast<lua_Integer>(static_cast<lua_Integer>(n) + 1)); // Hi monica, I am sorry. - Matt J.
        if (type != LUA_TSTRING)
        {
            const char* msg =
                lua_pushfstring(L, "bad table index #%d (string expected, got %s)", n + 1, lua_typename(L, type));
            return luaL_argerror(L, 2, msg);
        }

        size_t length = 0ULL;
        const char* text = luaL_tolstring(L, -1, &length);

        choices[n] = std::string(text, length);
    }

    lua_pushliteral(L, "_MANAGER");
    lua_rawget(L, LUA_REGISTRYINDEX);
    auto* manager = static_cast<NovelRT::Scripting::ScriptManager*>(lua_touserdata(L, -1));

    auto* data = new NovelRT::Scripting::Statuses::Branch(it->prompt, choices, L, manager->shared_from_this());
    lua_pushlightuserdata(L, data);
    return lua_yieldk(L, 1, 0, ProduceChoices_Cont);
}

luaL_Reg ChoiceFuncs[]{
    {"__call", ProduceChoices},
    {"__gc", CleanupChoice},
    {nullptr, nullptr},
};

void RegisterChoice(lua_State* L)
{
    if (luaL_newmetatable(L, "Choice") == 0)
        throw new NovelRT::Exceptions::InvalidOperationException("How did you get here?");

    luaL_setfuncs(L, ChoiceFuncs, 0);
}
