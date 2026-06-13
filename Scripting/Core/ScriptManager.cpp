// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <cstdlib>
#include <cstdint>
#include <format>
#include <random>

#include <Bindings/Bindings.hpp>

namespace NovelRT::Scripting
{
    void ScriptManager::CloseState::operator()(lua_State* L)
    {
        lua_close(L);
    }

    ScriptManager::ScriptManager() : _state(Bindings::CreateState())
    {
        lua_pushliteral(GetLuaState(), "_MANAGER");
        lua_pushlightuserdata(GetLuaState(), this);
        lua_rawset(GetLuaState(), LUA_REGISTRYINDEX);
    }

    lua_State* ScriptManager::GetLuaState() const
    {
        return _state.get();
    }

    std::unique_ptr<DecisionTree> ScriptManager::LoadDecisionTree(std::span<uint8_t> byteData)
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
            static_cast<void*>(&byteData), "decision_tree", nullptr);

        if (status != LUA_OK)
            throw NovelRT::Exceptions::InvalidOperationException(
                std::format("Failed to load decision tree, status={0}", status));

        // function is now at the top of the stack
        return std::make_unique<DecisionTree>(shared_from_this());
    }

}
