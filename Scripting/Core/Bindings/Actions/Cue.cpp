// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/DecisionTreeCue.hpp>
#include <NovelRT/Scripting/Cues/CompoundCue.hpp>
#include <NovelRT/Scripting/Statuses/TriggerCue.hpp>

#include "../Bindings.hpp"

#include <memory>
#include <vector>

struct CueInfo
{
    std::unique_ptr<NovelRT::Scripting::DecisionTreeCue> cue;
};

int TriggerCue_Cont(lua_State*, int, lua_KContext)
{
    // TODO: function-valued cues should return their parameters

    return 0;
}

int TriggerCue(lua_State* L)
{
    CueInfo* it = static_cast<CueInfo*>(luaL_checkudata(L, -1, "Cue"));

    if (it->cue == nullptr)
        return luaL_argerror(L, 1, "Attempted to trigger an invalid cue (it was likely used as part of a compound cue)");

    lua_pushliteral(L, "_MANAGER");
    lua_rawget(L, LUA_REGISTRYINDEX);
    auto* manager = static_cast<NovelRT::Scripting::ScriptManager*>(lua_touserdata(L, -1));

    auto* data = new NovelRT::Scripting::Statuses::TriggerCue(it->cue.get(), L, manager->shared_from_this());
    lua_pushlightuserdata(L, data);
    return lua_yieldk(L, 1, 0, TriggerCue_Cont);
}

int CreateCue(lua_State* L, std::unique_ptr<NovelRT::Scripting::DecisionTreeCue> cue)
{
    void* buffer = lua_newuserdatauv(L, sizeof(CueInfo), 0);
    luaL_setmetatable(L, "Cue");

    new(buffer) CueInfo{std::move(cue)};

    return 1;
}

const NovelRT::Scripting::DecisionTreeCue* GetCue(lua_State* L, int idx)
{
    auto* info = static_cast<CueInfo*>(luaL_testudata(L, idx, "Cue"));
    if (info == nullptr) return nullptr;

    return info->cue.get();
}

int CleanupCue(lua_State* L)
{
    CueInfo* it = static_cast<CueInfo*>(luaL_checkudata(L, -1, "Cue"));
    // Because we're using placement new, we need to manually call the destructor to ensure it gets cleaned up.
    it->~CueInfo();
    return 0;
}

// TODO: function-valued cues with parameters, which should only expect size == 1
luaL_Reg CueTableFunctions[]{
    {"compound", CreateCompoundCue},
    {"sfx", CreateSoundEffectCue},
    // {"animate", CreateAnimationCue},
    {"pose", CreateSetPoseCue},
    {nullptr, nullptr}
};

luaL_Reg CueMetaFunctions[] {
    {"__call", TriggerCue},
    {"__gc", CleanupCue},
    {nullptr, nullptr}
};

void RegisterCue(lua_State* L)
{
    if (luaL_newmetatable(L, "Cue") == 0)
    {
        throw NovelRT::Exceptions::InvalidOperationException("How did you get here?");
    }

    luaL_setfuncs(L, CueMetaFunctions, 0);
    lua_pop(L, 1);

    luaL_newlib(L, CueTableFunctions);
    lua_setglobal(L, "cue");
}
