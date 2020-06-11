// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_LUA_LUARUNNER_H
#define NOVELRT_LUA_LUARUNNER_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Lua {
  class LuaRunner {
  private:
    std::string _fileName;
    sol::state _state;

  public:
    LuaRunner::LuaRunner(const std::string& fileName) noexcept;
    void init();
    void run();
  };
}

#endif //!NOVELRT_LUA_LUARUNNER_H
