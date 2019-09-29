//
// Created by Tyler on 29/09/2019.
//

#ifndef NOVELRT_LUAARGUMENTS_H
#define NOVELRT_LUAARGUMENTS_H
#include <lua.h>
namespace NovelRT::Lua {
class LuaArguments {
  template <typename... T> void pushToStack(lua_State *l, T... args);
};
}
#endif // NOVELRT_LUAARGUMENTS_H
