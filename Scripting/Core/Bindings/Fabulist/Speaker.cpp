// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

#include "../Bindings.hpp"

struct SpeakerInfo
{
    std::string name;
};

int CreateSpeaker(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);
    void* buffer = lua_newuserdatauv(L, sizeof(SpeakerInfo), 0);
    luaL_setmetatable(L, "Speaker");

    // Because we're creating objects in memory we don't own, we need to use placement new.
    new (buffer) SpeakerInfo{name};

    lua_setglobal(L, name);

    return 1;
}

int CleanupSpeaker(lua_State* L)
{
    SpeakerInfo* it = static_cast<SpeakerInfo*>(luaL_checkudata(L, 1, "Speaker"));
    // Because we're using placement new, we need to manually call the destructor to ensure it gets cleaned up.
    it->~SpeakerInfo();
    return 0;
}

int ProduceSpeakerLine_Cont(lua_State* L, int, lua_KContext)
{
    lua_pushvalue(L, 1);
    return 1;
}

int ProduceSpeakerLine(lua_State* L)
{
    SpeakerInfo* it = static_cast<SpeakerInfo*>(luaL_checkudata(L, 1, "Speaker"));
    const char* text = luaL_checkstring(L, 2);

    lua_pushliteral(L, "_MANAGER");
    lua_rawget(L, LUA_REGISTRYINDEX);
    auto* manager = static_cast<NovelRT::Scripting::ScriptManager*>(lua_touserdata(L, -1));

    auto* data = new NovelRT::Scripting::Statuses::SpokenLine(it->name, text, L, manager->shared_from_this());
    lua_pushlightuserdata(L, data);
    return lua_yieldk(L, 1, 0, ProduceSpeakerLine_Cont);
}

luaL_Reg SpeakerFuncs[]{
    {"__call", ProduceSpeakerLine},
    {"__gc", CleanupSpeaker},
    {nullptr, nullptr},
};

void RegisterSpeaker(lua_State* L)
{
    if (luaL_newmetatable(L, "Speaker") == 0)
        throw new NovelRT::Exceptions::InvalidOperationException("How did you get here?");

    luaL_setfuncs(L, SpeakerFuncs, 0);
}
