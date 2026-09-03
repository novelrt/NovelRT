// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/Cues/PlaySoundEffectCue.hpp>

#include "../Bindings.hpp"

struct SoundInfo
{
    std::string path;
    double pitch = 1;
};

int CreateSoundEffectCue(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    SoundInfo info;
    if (lua_getfield(L, 1, "sound") == LUA_TSTRING)
    {
        std::size_t pathLength;
        const char* path = luaL_tolstring(L, -1, &pathLength);
        info.path = std::string(path, pathLength);
        lua_pop(L, 1);
    }
    else
    {
        return NovelRT::FieldTypeError(L, 1, -1, "sound", lua_typename(L, LUA_TSTRING));
    }

    if (lua_getfield(L, 1, "pitch") == LUA_TNUMBER)
    {
        info.pitch = lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    else if (!lua_isnoneornil(L, -1))
    {
        return NovelRT::FieldTypeError(L, 1, -1, "pitch", lua_typename(L, LUA_TNUMBER));
    }

    return CreateCue(L, std::make_unique<NovelRT::Scripting::Cues::PlaySoundEffectCue>(info.path, info.pitch));
}
