// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <cstdint>
#include <cstdlib>
#include <format>
#include <random>

#include "Bindings/Bindings.hpp"

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

    lua_State* CreateState()
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
        RegisterFabulist(L);

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

    void ScriptManager::CloseState::operator()(lua_State* L)
    {
        lua_close(L);
    }

    ScriptManager::ScriptManager() : _state(CreateState())
    {
        lua_pushliteral(GetLuaState(), "_MANAGER");
        lua_pushlightuserdata(GetLuaState(), this);
        lua_rawset(GetLuaState(), LUA_REGISTRYINDEX);
    }

    lua_State* ScriptManager::GetLuaState() const
    {
        return _state.get();
    }

    std::unique_ptr<DecisionTree> ScriptManager::LoadDecisionTree(std::span<const uint8_t> byteData)
    {
        return LoadDecisionTree(byteData, "decision_tree");
    }

    std::unique_ptr<DecisionTree> ScriptManager::LoadDecisionTree(std::span<const uint8_t> byteData, std::string name)
    {
        auto status = lua_load(
            _state.get(),
            [](lua_State*, void* data, size_t* size) -> const char*
            {
                std::span<uint8_t>* bytes = static_cast<std::span<uint8_t>*>(data);

                if (bytes->empty())
                    return nullptr;
                *size = bytes->size_bytes();
                const char* result = reinterpret_cast<const char*>(bytes->data());
                *bytes = bytes->last(0);
                return result;
            },
            static_cast<void*>(&byteData), name.c_str(), nullptr);

        if (status != LUA_OK)
            throw NovelRT::Exceptions::InvalidOperationException(
                std::format("Failed to load decision tree, status={0}", status));

        // function is now at the top of the stack
        return std::make_unique<DecisionTree>(shared_from_this());
    }

}
