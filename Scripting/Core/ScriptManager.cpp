// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/ScriptManager.hpp>
#include <NovelRT/Scripting/DecisionTree.hpp>

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <cstdlib>
#include <format>
#include <random>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

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

    int RegisterFabulistMethods(lua_State* L) {
        luaL_Reg funcs[]{
            {"speaker", nullptr}, // TODO: this needs a func
            {nullptr, nullptr}
        };

        lua_pushglobaltable(L);
        luaL_setfuncs(L, funcs, 0);

        // Remove potentially problematic base lib functions
        lua_pushnil(L);
        lua_setfield(L, -2, "collectgarbage");
        lua_pushnil(L);
        lua_setfield(L, -2, "dofile");
        lua_pushnil(L);
        lua_setfield(L, -2, "loadfile");
        lua_pushnil(L);
        lua_setfield(L, -2, "load");

        return 1;
    }

    lua_State* CreateState()
    {
        std::random_device r;
        lua_State* L = lua_newstate(AllocMemory, nullptr, r());
        // TODO: probably should handle this
        if (L == nullptr) return nullptr;

        lua_atpanic(L, Panic);
        luaL_openselectedlibs(L,
            LUA_GLIBK | LUA_STRLIBK | LUA_UTF8LIBK | LUA_TABLIBK | LUA_MATHLIBK,
            0);
        luaL_requiref(L, "fabulist", RegisterFabulistMethods, false);

        return L;
    }

    void ScriptManager::CloseState::operator()(lua_State* L)
    {
        lua_close(L);
    }


    ScriptManager::ScriptManager()
        : _state(CreateState())
    { }

    lua_State* ScriptManager::GetLuaState() const
    {
        return _state.get();
    }

    std::unique_ptr<DecisionTree> ScriptManager::LoadDecisionTree(std::span<uint8_t> byteData)
    {
        auto status = lua_load(_state.get(),
                 [](lua_State*, void* data, size_t* size){
                    std::span<uint8_t>* bytes = static_cast<std::span<uint8_t>*>(data);
                    *size = bytes->size_bytes();
                    return reinterpret_cast<const char*>(bytes->data());
                 },
                 static_cast<void*>(&byteData),
                 "decision_tree",
                 nullptr);

        if (status != LUA_OK)
            throw NovelRT::Exceptions::InvalidOperationException(std::format("Failed to load decision tree, status={0}", status));

        // function is now at the top of the stack
        return std::make_unique<DecisionTree>(shared_from_this());
    }

}
