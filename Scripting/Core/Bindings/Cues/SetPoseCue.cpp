// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/Cues/SetPoseCue.hpp>

#include "../Bindings.hpp"

struct PoseInfo
{
    std::string character;
    std::string pose;
};

int CreateSetPoseCue(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    PoseInfo info{};
    if (lua_getfield(L, 1, "character") == LUA_TSTRING)
    {
        std::size_t characterLength;
        const char* character = luaL_tolstring(L, -1, &characterLength);
        info.character = std::string(character, characterLength);
        lua_pop(L, 1);
    }
    else
    {
        return NovelRT::FieldTypeError(L, 1, -1, "character", lua_typename(L, LUA_TSTRING));
    }

    if (lua_getfield(L, 1, "pose") == LUA_TSTRING)
    {
        std::size_t poseLength;
        const char* pose = luaL_tolstring(L, -1, &poseLength);
        info.pose = std::string(pose, poseLength);
        lua_pop(L, 1);
    }
    else
    {
        return NovelRT::FieldTypeError(L, 1, -1, "pose", lua_typename(L, LUA_TSTRING));
    }

    return CreateCue(L, std::make_unique<NovelRT::Scripting::Cues::SetPoseCue>(info.character, info.pose));
}
