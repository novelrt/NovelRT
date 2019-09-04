//
// Created by Tyler on 04/09/2019.
//

#include <lua.hpp>
#include <string>
#include "LuaRunner.h"
namespace NovelRT::Lua {

LuaRunner::LuaRunner(const std::string& fileName) {
  _fileName = fileName.c_str();
  _state = luaL_newstate();
}
};
