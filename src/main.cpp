#include "Lua/LuaRunner.h"
#include "NovelCommonArgs.h"
#include "NovelImageRect.h"
#include "NovelLayeringService.h"
#include "NovelRenderingService.h"
#include "NovelRunner.h"
#include <iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
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

NovelRT::NovelRunner* _runner;

static int draw(lua_State* l) {

  printf("called");

  auto rectArgs = NovelRT::NovelCommonArgs();
  rectArgs.startingPosition.setY(1080 / 2);
  rectArgs.startingPosition.setX((1080 / 2) + 400);
  rectArgs.layer = 0;
  rectArgs.orderInLayer = 1;
  rectArgs.startingRotation = 0.0f;

  _runner->getRenderer()->getBasicFillRect(
      NovelRT::GeoVector<float>(200, 200),
          NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);

  return 2;
}

#ifdef WIN32
#define setenv(name, value, overwrite) \
    static_assert(overwrite != 0);     \
    _putenv_s(name, value)
#endif

NovelRT::NovelBasicFillRect* basicFillRect;
NovelRT::NovelImageRect* novelChanRect;

int main(int argc, char* argv[]) {
  //setenv("DISPLAY", "localhost:0", true);
  //L = luaL_newstate();
  //luaL_openlibs(L);
  //lua_register(L, "average", average);
  //luaL_dofile(L, "avg.lua");
  //lua_close(L);

  auto runner = NovelRT::NovelRunner(0, new NovelRT::NovelLayeringService());

  auto luaRunner = NovelRT::Lua::LuaRunner("test.lua");
  luaRunner.registerMethod("drawSquare", draw);

  _runner = &runner;

  luaRunner.run();

  NovelRT::NovelCommonArgs novelChanArgs;
  novelChanArgs.layer = 0;
  novelChanArgs.orderInLayer = 0;
  novelChanArgs.startingPosition.setX(1920 / 2);
  novelChanArgs.startingPosition.setY(1080 / 2);

  novelChanRect = runner.getRenderer()->getImageRect(NovelRT::GeoVector<float>(456, 618), "novel-chan.png", novelChanArgs);

  //auto rectArgs = NovelRT::NovelCommonArgs();
  //rectArgs.startingPosition = novelChanArgs.startingPosition;
  //rectArgs.startingPosition.setX(rectArgs.startingPosition.getX() + 400);
  //rectArgs.layer = 0;
  //rectArgs.orderInLayer = 1;
  //rectArgs.startingRotation = 0.0f;

  //basicFillRect = runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);

  runner.runOnUpdate([](const float delta) {
    const float rotationAmount = 45.0f;

    auto rotation = novelChanRect->getRotation();
    rotation += rotationAmount * delta;

    if (rotation > 360.0f)
    {
      rotation -= 360.0f;
    }

    novelChanRect->setRotation(rotation);
  });


  //auto rect = runner.getInteractionService()->getBasicInteractionRect(NovelRT::GeoVector<float>(200, 200), rectArgs);
  //rect->subscribeToInteracted([]{novelChanRect->setActive(!novelChanRect->getActive());});


  runner.runNovel();

  return 0;
}

