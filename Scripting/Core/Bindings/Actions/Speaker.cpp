// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

#include "../Bindings.hpp"

#include <optional>
#include <string>
#include <unordered_map>

struct PoseInfo
{
    std::string sprite;
    double xPos = 0;
    double yPos = 0;
    double xScale = 1;
    double yScale = 1;
};

struct SpeakerInfo
{
    std::string name;
    std::optional<std::string> activePose;
    std::unordered_map<std::string, PoseInfo> poses;
};

PoseInfo ReadPoseInfo(lua_State* L, int arg, int idx, const char* name)
{
    idx = lua_absindex(L, idx);
    PoseInfo result;

    if (lua_getfield(L, idx, "sprite") == LUA_TSTRING)
    {
        std::size_t spriteLength;
        const char* sprite = lua_tolstring(L, -1, &spriteLength);
        result.sprite = std::string(sprite, spriteLength);
        lua_pop(L, 1);
    }
    else if (!lua_isnoneornil(L, -1))
    {
        int spriteIdx = lua_absindex(L, -1);
        NovelRT::FieldTypeError(L, arg, spriteIdx, lua_pushfstring(L, "poses.%s.sprite", name), lua_typename(L, LUA_TSTRING));
    }

    if (lua_getfield(L, idx, "position") == LUA_TTABLE)
    {
        if (lua_rawgeti(L, -1, 1) != LUA_TNUMBER)
        {
            int positionIdx = lua_absindex(L, -1);
            NovelRT::FieldTypeError(L, arg, positionIdx, lua_pushfstring(L, "poses.%s.position[1]", name), lua_typename(L, LUA_TNUMBER));
        }
        result.xPos = lua_tonumber(L, -1);
        lua_pop(L, 1);

        if (lua_rawgeti(L, -1, 2) != LUA_TNUMBER)
        {
            int positionIdx = lua_absindex(L, -1);
            NovelRT::FieldTypeError(L, arg, positionIdx, lua_pushfstring(L, "poses.%s.position[2]", name), lua_typename(L, LUA_TNUMBER));
        }
        result.yPos = lua_tonumber(L, -1);
        lua_pop(L, 2);
    }
    else if (!lua_isnoneornil(L, -1))
    {
        int positionIdx = lua_absindex(L, -1);
        NovelRT::FieldTypeError(L, arg, positionIdx, lua_pushfstring(L, "poses.%s.position", name), lua_typename(L, LUA_TNUMBER));
    }

    if (lua_getfield(L, idx, "scale") == LUA_TTABLE)
    {
        if (lua_rawgeti(L, -1, 1) != LUA_TNUMBER)
        {
            int scaleIdx = lua_absindex(L, -1);
            NovelRT::FieldTypeError(L, arg, scaleIdx, lua_pushfstring(L, "poses.%s.scale[1]", name), lua_typename(L, LUA_TNUMBER));
        }
        result.xScale = lua_tonumber(L, -1);
        lua_pop(L, 1);

        if (lua_rawgeti(L, -1, 2) != LUA_TNUMBER)
        {
            int scaleIdx = lua_absindex(L, -1);
            NovelRT::FieldTypeError(L, arg, scaleIdx, lua_pushfstring(L, "poses.%s.scale[2]", name), lua_typename(L, LUA_TNUMBER));
        }
        result.yScale = lua_tonumber(L, -1);
        lua_pop(L, 2);
    }
    else if (!lua_isnoneornil(L, -1))
    {
        int scaleIdx = lua_absindex(L, -1);
        NovelRT::FieldTypeError(L, arg, scaleIdx, lua_pushfstring(L, "poses.%s.scale", name), lua_typename(L, LUA_TNUMBER));
    }

    return result;
}

std::unordered_map<std::string, PoseInfo> ReadPoses(lua_State* L, int arg, int idx)
{
    idx = lua_absindex(L, idx);

    std::unordered_map<std::string, PoseInfo> result;

    lua_pushnil(L);
    while (lua_next(L, idx) != 0)
    {
        // N.B. we want to keep track of the stack position so that the body of the loop doesn't affect our iteration
        int top = lua_gettop(L);

        if (lua_type(L, -2) != LUA_TSTRING)
        {
            int keyIdx = lua_absindex(L, -2);
            NovelRT::FieldTypeError(L, arg, keyIdx, lua_pushfstring(L, "poses.%s", luaL_tolstring(L, -2, nullptr)),
                                    lua_typename(L, LUA_TSTRING));
        }

        if (lua_type(L, -1) != LUA_TTABLE)
        {
            int valueIdx = lua_absindex(L, -1);
            NovelRT::FieldTypeError(L, arg, valueIdx, lua_pushfstring(L, "poses.%s", luaL_tolstring(L, -2, nullptr)),
                                    lua_typename(L, LUA_TTABLE));
        }

        std::size_t length;
        const char* key = lua_tolstring(L, -2, &length);
        result[std::string(key, length)] = ReadPoseInfo(L, arg, -1, key);

        // Restore the stack and pop the value so that we can continue iterating.
        lua_settop(L, top);
        lua_pop(L, 1);
    }

    return result;
}

int SetSpeakerAdditionalProps(lua_State* L)
{
    SpeakerInfo* it = static_cast<SpeakerInfo*>(lua_touserdata(L, lua_upvalueindex(1)));
    luaL_checktype(L, 1, LUA_TTABLE);

    if (lua_getfield(L, 1, "poses") == LUA_TTABLE)
    {
        it->poses = ReadPoses(L, 1, -1);
        if (it->poses.size() > 0)
            it->activePose = it->poses.begin()->first;
    }
    else if (!lua_isnoneornil(L, -1))
    {
        return NovelRT::FieldTypeError(L, 1, -1, "poses", lua_typename(L, LUA_TTABLE));
    }

    if (lua_getfield(L, 1, "pose") == LUA_TSTRING)
    {
        std::size_t pLength;
        const char* p = luaL_tolstring(L, -1, &pLength);
        std::string pose(p, pLength);

        if (auto search = it->poses.find(pose); search == it->poses.end())
        {
            const char* msg = lua_pushfstring(L, "bad field %s (unknown pose %s)", "pose", p);
            return luaL_argerror(L, 1, msg);
        }

        it->activePose = pose;
    }
    else if (!lua_isnoneornil(L, -1))
    {
        return NovelRT::FieldTypeError(L, 1, -1, "pose", lua_typename(L, LUA_TSTRING));
    }

    lua_pushvalue(L, lua_upvalueindex(1));
    return 1;
}

int CreateSpeaker(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);
    void* buffer = lua_newuserdatauv(L, sizeof(SpeakerInfo), 0);
    luaL_setmetatable(L, "Speaker");

    // Because we're creating objects in memory we don't own, we need to use placement new.
    new (buffer) SpeakerInfo{name, std::nullopt, {}};

    // Associate the speaker with the global by that name
    lua_pushvalue(L, -1);
    lua_setglobal(L, name);

    // Allow the user to configure the speaker
    lua_pushvalue(L, -1);
    lua_pushcclosure(L, SetSpeakerAdditionalProps, 1);
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
    {
        throw NovelRT::Exceptions::InvalidOperationException("How did you get here?");
    }

    luaL_setfuncs(L, SpeakerFuncs, 0);
}
