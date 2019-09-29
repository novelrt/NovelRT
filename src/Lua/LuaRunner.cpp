//
// Created by Tyler on 04/09/2019.
//

#include "LuaRunner.h"
#include "LuaArguments.h"
#include <iostream>
#include <lua.hpp>
#include <string>
namespace NovelRT::Lua {

LuaRunner::LuaRunner(const std::string& fileName) {
  std::cout << "IN CTOR: " << _fileName << std::endl;
  _fileName = fileName;
  _state = luaL_newstate();
  luaL_openlibs(_state);
}

void LuaRunner::registerMethod(const char* name, lua_CFunction fn) {
  lua_register(_state, name, fn);
}

void LuaRunner::run() {
  std::cout << _fileName << std::endl;
  luaL_dofile(_state, _fileName.c_str());
}
template<typename... TArgs>
LuaMethodResult LuaRunner::runMethod(std::string name, TArgs... args, int resultAmount) {
  lua_getglobal(_state, name);
  auto args = LuaArguments(_state, args);
  lua_call(_state, sizeof...(TArgs), resultAmount);
  auto results = LuaMethodResult(_state);
  return results;
}

void LuaRunner::stop() {
  lua_close(_state);
}
};
