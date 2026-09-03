// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "Bindings.hpp"

namespace NovelRT
{
    int FieldTypeError(lua_State* L, int arg, int idx, const char* field, const char* tname)
    {
        // This logic is the same as luaL_typeerror
        const char* typearg;
        if (luaL_getmetafield(L, idx, "__name") == LUA_TSTRING)
        {
            typearg = lua_tostring(L, -1);
        }
        else if (lua_type(L, idx) == LUA_TLIGHTUSERDATA)
        {
            typearg = "light userdata";
        }
        else
        {
            typearg = luaL_typename(L, idx);
        }

        const char* msg = lua_pushfstring(L, "bad field %s (%s expected, got %s)", field, tname, typearg);
        return luaL_argerror(L, arg, msg);
    }
}
