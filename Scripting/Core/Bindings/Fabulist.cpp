// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

#include "Bindings.hpp"

luaL_Reg DefaultFunctions[]{
    {"speaker", CreateSpeaker},
    {"choice", CreateChoice},
    {nullptr, nullptr},
};

void RegisterFabulist(lua_State* L)
{
    lua_pushglobaltable(L);
    luaL_setfuncs(L, DefaultFunctions, 0);
    lua_pop(L, 1);

    RegisterSpeaker(L);
    RegisterChoice(L);
    RegisterCue(L);
}
