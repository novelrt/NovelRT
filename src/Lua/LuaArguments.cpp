//
// Created by Tyler on 29/09/2019.
//

#include "LuaArguments.h"

extern "C" {
#include <lua.h>
#include <lua.hpp>
#include <luaconf.h>
#include <lualib.h>
}

namespace NovelRT::Lua {
template<typename... T>
void LuaArguments::pushToStack(lua_State* l, T... args) {
  if(typeid(args).name() == typeid(std::string).name()) {
    lua_pushstring(l, args);
  } else if(typeid(args).name() == typeid(int).name()) {
    lua_pushnumber(L, args);
  }

  pushToStack(l, args...);
}
}
