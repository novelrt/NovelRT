//
// Created by Tyler on 04/09/2019.
//

#ifndef NOVELRT_LUARUNNER_H
#define NOVELRT_LUARUNNER_H

extern "C" {
#include <lua.h>
};

#include "LuaMethodResult.h"
#include <string>
namespace NovelRT::Lua {
class LuaRunner {
private:
  lua_State* _state;
  std::string _fileName;
public:
  explicit LuaRunner(const std::string& fileName);
  void run();
  void stop();
  void registerMethod(const char* name, lua_CFunction fn);
  template <typename... TArgs> LuaMethodResult runMethod(std::string name, TArgs... args, int resultAmount);
};
}

#endif //NOVELRT_SRC_LUA_LUARUNNER_H
