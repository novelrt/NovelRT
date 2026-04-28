// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/ScriptManager.hpp>

#include <exception>
#include <cstdlib>
#include <random>

#include <lua.h>

namespace NovelRT::Scripting
{
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

    int Panic(lua_State*) {
        // TODO: the error object is on the top of the stack, we should log it.
        std::terminate();
        return 0;
    }

    lua_State* CreateState()
    {
        std::random_device r;
        lua_State* L = lua_newstate(AllocMemory, nullptr, r());
        if (L) lua_atpanic(L, Panic);
        return L;
    }

    void ScriptManager::CloseState::operator()(lua_State* L)
    {
        lua_close(L);
    }



    ScriptManager::ScriptManager()
        : _state()
    { }

}
