// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/Cues/CompoundCue.hpp>

#include "../Bindings.hpp"

#include <memory>
#include <vector>


int CreateCompoundCue(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    int size = int(lua_rawlen(L, 1));

    if (size == 1)
    {
        lua_rawgeti(L, 1, 1);
        return 1;
    }

    std::vector<std::unique_ptr<NovelRT::Scripting::DecisionTreeCue>> compound;
    for (int n = 1; n <= size; n++)
    {
        int type = lua_rawgeti(L, 1, n);

        switch (type)
        {
            case LUA_TUSERDATA:
            {
                auto action = GetCue(L, -1);
                int idx = lua_absindex(L, -1);
                if (action == nullptr) return NovelRT::FieldTypeError(L, 1, idx, lua_pushfstring(L, "cue[%d]", n), "Cue");
                // using std::move here will ensure that CueAction's action is set to nullptr properly.
                compound.emplace_back(action->Clone());
                break;
            }
            default:
            {
                int idx = lua_absindex(L, -1);
                return NovelRT::FieldTypeError(L, 1, idx, lua_pushfstring(L, "cue[%d]", n), "Cue");
            }
        }

        lua_pop(L, 1);
    }

    return CreateCue(L, std::make_unique<NovelRT::Scripting::Cues::CompoundCue>(std::move(compound)));
}
