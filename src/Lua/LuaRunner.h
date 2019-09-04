//
// Created by Tyler on 04/09/2019.
//

#ifndef NOVELRT_LUARUNNER_H
#define NOVELRT_LUARUNNER_H

#include <lua.h>
#include <string>
namespace NovelRT::Lua {
class LuaRunner {
private:
  lua_State* _state;
  const char* _fileName;
public:
  LuaRunner(const std::string& fileName);
};
&}

#endif //NOVELRT_SRC_LUA_LUARUNNER_H
