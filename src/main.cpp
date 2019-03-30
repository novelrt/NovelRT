#include <iostream>
#include "NovelRenderingService.h"
#include "NovelRunner.h"
#include "NovelImageRect.h"
#include "NovelCommonArgs.h"
#include "NovelLayeringService.h"

extern "C" {
#include "../lib/lua53/lua.h"
#include "../lib/lua53/lualib.h"
#include "../lib/lua53/lauxlib.h"
}

lua_State* L;

static int average(lua_State* L) {
  int n = lua_gettop(L);
  double sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += lua_tonumber(L, i);
  }
  lua_pushnumber(L, sum / n);
  lua_pushnumber(L, sum);
  return 2;
}

int main() {
  //setenv("MESA_GL_VERSION_OVERRIDE", "3.2", true);
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "average", average);
  luaL_dofile(L, "avg.lua");
  lua_close(L);
  auto runner = NovelRT::NovelRunner(0, new NovelRT::NovelLayeringService());
  NovelRT::NovelCommonArgs yuriArgs;
  yuriArgs.layer = 0;
  yuriArgs.orderInLayer = 0;
  yuriArgs.startingPosition.setX(1920 / 2);
  yuriArgs.startingPosition.setY(1080 / 2);

  runner.getRenderer()->getImageRect("test-yuri.png", yuriArgs);

  auto rectArgs = NovelRT::NovelCommonArgs();
  rectArgs.startingPosition = yuriArgs.startingPosition;
  rectArgs.layer = 1;
  rectArgs.orderInLayer = 1;

  runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(500, 500), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);


  runner.runNovel();
}