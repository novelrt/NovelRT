// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdlib>
#include <exception>
#include <random>

#include "../Bindings.hpp"

// It may be worth implementing some sort of tracking here so we can limit the amount of memory used by Lua
void* AllocMemory(void*, void* pointer, size_t, size_t size)
{
    if (size == 0)
    {
        std::free(pointer);
        return nullptr;
    }

    return std::realloc(pointer, size);
}

int Panic(lua_State*)
{
    // TODO: the error object is on the top of the stack, we should log it.
    std::terminate();
    return 0;
}

lua_State* NovelRT::Scripting::Bindings::CreateState()
{
    std::random_device r;
    lua_State* L = lua_newstate(AllocMemory, nullptr, r());
    // TODO: probably should handle this
    if (L == nullptr)
        return nullptr;

    lua_atpanic(L, Panic);
    luaL_openselectedlibs(L, LUA_GLIBK | LUA_STRLIBK | LUA_UTF8LIBK | LUA_TABLIBK | LUA_MATHLIBK, 0);
    luaL_requiref(L, "fabulist", RegisterFabulist, false);

    lua_pushglobaltable(L);

    // Remove potentially problematic base lib functions
    lua_pushnil(L);
    lua_setfield(L, -2, "collectgarbage");
    lua_pushnil(L);
    lua_setfield(L, -2, "dofile");
    lua_pushnil(L);
    lua_setfield(L, -2, "loadfile");
    lua_pushnil(L);
    lua_setfield(L, -2, "load");

    lua_pop(L, 1);

    return L;
}
