#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeCue.hpp>

#include <memory>

// clang-format off
// Lua includes operate in this order.
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
// clang-format on

namespace NovelRT
{
    int FieldTypeError(lua_State* L, int arg, int idx, const char* field, const char* tname);
}

void RegisterFabulist(lua_State* L);

void RegisterSpeaker(lua_State* L);
void RegisterChoice(lua_State* L);
void RegisterCue(lua_State* L);

int CreateSpeaker(lua_State* L);
int CreateChoice(lua_State* L);

int CreateCue(lua_State* L, std::unique_ptr<NovelRT::Scripting::DecisionTreeCue> action);
const NovelRT::Scripting::DecisionTreeCue* GetCue(lua_State* L, int idx);

int CreateCompoundCue(lua_State* L);
int CreateSoundEffectCue(lua_State* L);
//int CreateAnimationCue(lua_State* L);
int CreateSetPoseCue(lua_State* L);
