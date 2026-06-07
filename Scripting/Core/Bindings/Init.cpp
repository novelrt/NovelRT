// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdlib>
#include <exception>
#include <format>
#include <new>
#include <random>
#include <stdexcept>

#include <Bindings/Bindings.hpp>

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

int Panic(lua_State* L)
{
    lua_checkstack(L, 1);
    size_t length;
    const char* msg = lua_tolstring(L, 1, &length);
    // Lua would normally call abort(), but if we throw we'll get passed back to whichever stack frame handles
    // runtime_error
    // TODO: maybe we should introduce a custom exception for this?
    throw std::runtime_error{std::format("Unexpected error in Lua: {}", std::string(msg, length))};
}

lua_State* NovelRT::Scripting::Bindings::CreateState()
{
    std::random_device r;
    lua_State* L = lua_newstate(AllocMemory, nullptr, r());
    if (L == nullptr)
    {
        // If the allocation failed, make sure we report that up the chain.
        throw std::bad_alloc{};
    }

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
