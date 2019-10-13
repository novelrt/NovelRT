#include <iostream>
#include "NovelRenderingService.h"
#include "NovelRunner.h"
#include "NovelImageRect.h"
#include "NovelCommonArgs.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

lua_State* L;

static int average(lua_State* luaState) {
  int n = lua_gettop(luaState);
  double sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += lua_tonumber(luaState, i);
  }
  lua_pushnumber(luaState, sum / n);
  lua_pushnumber(luaState, sum);
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
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "average", average);
  luaL_dofile(L, "avg.lua");
  lua_close(L);
  auto runner = NovelRT::NovelRunner(0);
  NovelRT::NovelCommonArgs novelChanArgs;
  novelChanArgs.layer = 0;
  novelChanArgs.orderInLayer = 0;
  novelChanArgs.startingPosition.setX(1920 / 2);
  novelChanArgs.startingPosition.setY(1080 / 2);

  novelChanRect = runner.getRenderer()->getImageRect(NovelRT::GeoVector<float>(456, 618), "novel-chan.png", novelChanArgs, NovelRT::RGBAConfig(255, 0, 255, 255));

  auto rectArgs = NovelRT::NovelCommonArgs();
  rectArgs.startingPosition = novelChanArgs.startingPosition;
  rectArgs.startingPosition.setX(rectArgs.startingPosition.getX() + 400);
  rectArgs.startingPosition.setY(rectArgs.startingPosition.getY() - 400);
  rectArgs.layer = 0;
  rectArgs.orderInLayer = 1;
  rectArgs.startingRotation = 0.0f;

  basicFillRect = runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);
  auto textRect = runner.getRenderer()->getTextRect(NovelRT::RGBAConfig(0, 255, 0, 255), 70, "Gayathri-Regular.ttf", rectArgs);
  textRect->setText("RubyGnomer");

  runner.getDebugService()->setIsFpsCounterVisible(true);

  runner.runOnUpdate([](const double delta) {
    const float rotationAmount = 45.0f;

    auto rotation = novelChanRect->getRotation();
    rotation += rotationAmount * (float)delta;

    if (rotation > 360.0f)
    {
      rotation -= 360.0f;
    }

    novelChanRect->setRotation(rotation);
  });


  auto rect = runner.getInteractionService()->getBasicInteractionRect(NovelRT::GeoVector<float>(200, 200), rectArgs);
  rect->subscribeToInteracted([]{novelChanRect->setActive(!novelChanRect->getActive());});


  runner.runNovel();

  return 0;
}

