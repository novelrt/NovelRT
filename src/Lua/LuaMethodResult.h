//
// Created by Tyler on 29/09/2019.
//

#ifndef NOVELRT_LUAMETHODRESULT_H
#define NOVELRT_LUAMETHODRESULT_H
#include <lua.h>
#include <tuple>
namespace NovelRT::Lua {
class LuaMethodResult {
public:
  explicit LuaMethodResult(lua_State* l);
  template<typename... T>
  std::tuple<T...> unpack(int amount);
private:
  lua_State* _l;
  int _indexer;
};
}
#endif // NOVELRT_LUAMETHODRESULT_H
