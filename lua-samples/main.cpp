// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

int main(int /*argc*/, char* /*argv*/[])
{
  auto luaRunner = NovelRT::Lua::LuaRunner("main.lua");
  luaRunner.init();
  luaRunner.run();
  return 0;
}
