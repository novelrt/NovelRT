#include <iostream>
#include "NovelRenderingService.h"
#include "NovelRunner.h"
#include "NovelImageRect.h"
#include "NovelCommonArgs.h"
#include "NovelLayeringService.h"
#include "NovelInteractionService.h"

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

#ifdef WIN32
#define setenv(name, value, overwrite) \
    static_assert(overwrite != 0);     \
    _putenv_s(name, value)
#endif

NovelRT::NovelBasicFillRect* basicFillRect;
NovelRT::NovelImageRect* yuri;

int main(int argc, char* argv[]) {
  //setenv("DISPLAY", "localhost:0", true);
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

  yuri = runner.getRenderer()->getImageRect(NovelRT::GeoVector<float>(200, 200), "test-yuri.png", yuriArgs);

  auto rectArgs = NovelRT::NovelCommonArgs();
  rectArgs.startingPosition = yuriArgs.startingPosition;
  rectArgs.startingPosition.setX(rectArgs.startingPosition.getX() + 400);
  rectArgs.layer = 0;
  rectArgs.orderInLayer = 1;
  rectArgs.startingRotation = 20.0f;

  //NovelRT::NovelInteractionService().consumePlayerInput();

  basicFillRect = runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);

  runner.runOnUpdate([](const float delta) {
    const float rotationAmount = 45.0f;

    auto rotation = basicFillRect->getRotation();
    rotation += rotationAmount * delta;

    if (rotation > 360.0f)
    {
      rotation -= 360.0f;
    }

    basicFillRect->setRotation(rotation);
    yuri->setRotation(-rotation);
  });

/*
  auto rect = runner.getInteractionService()->getBasicInteractionRect(NovelRT::GeoVector<float>(200, 200), rectArgs);
  rect->subscribeToInteracted([yuri]{yuri->setActive(!yuri->getActive());});
*/

  runner.runNovel();

  return 0;
}

