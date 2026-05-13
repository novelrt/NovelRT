#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// clang-format off
// Lua includes operate in this order.
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
// clang-format on

namespace NovelRT::Scripting::Bindings
{
    int RegisterFabulist(lua_State* L);

    lua_State* CreateState();
}
