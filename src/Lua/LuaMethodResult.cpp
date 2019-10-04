//
// Created by Tyler on 29/09/2019.
//

#include "LuaMethodResult.h"

namespace NovelRT::Lua {
  template<typename... T>
  std::tuple<T...> LuaMethodResult::unpack(int amount, std::tuple<T...> result) {

    std::tuple<T...> tuple;
    if(result == nullptr_t()) {
      tuple = std::tuple<T...>();
    }

    if(indexer >= amount) return tuple;

    // TODO: add more type converters
    if(typeof(T).name() == typeof(std::string).name()) {
      tuple = std::tuple_cat(tuple, std::make_tuple(lua_tostring(_l, -indexer++)));
    } else if(typeof(T).name() == typeof(int).name())) {
      tuple = std::tuple_cat(tuple, std::make_tuple(lua_tonumber(_l, -indexer++)));
    }

    unpack(amount, tuple);
  }
LuaMethodResult::LuaMethodResult(lua_State *l) {
  _l = l;
  _indexer = 0;
}
}
