//
// Created by Tyler on 04/09/2019.
//

#include "LuaRunner.h"
#include <lua.hpp>
#include <string>
namespace NovelRT::Lua {

LuaRunner::LuaRunner(const std::string& fileName) {
  _fileName = fileName.c_str();
  _state = luaL_newstate();
  luaL_openlibs(_state);
}

void LuaRunner::registerMethod(const char* name, lua_CFunction fn) {
  lua_register(_state, name, fn);
}

void LuaRunner::run() {
  std::cout << _fileName << std::endl;
  luaL_dofile(_state, _fileName);
}

void LuaRunner::stop() {
  lua_close(_state);
}
};
