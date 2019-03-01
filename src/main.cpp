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

static void is_prime() {

    lua_State* _L = luaL_newstate(); // create instance of lua stuff
    luaL_openlibs(_L); // open lua stdlibs

    if(luaL_loadfile(_L, "prime.lua")) { //load muh file
        std::cout << "loadfile failed" << std::endl;
    };

    lua_pcall(_L, 0, 0, 0); // this initalizes all stuff and things


    for(int i = 0; i < 10; i++) {

        lua_getglobal(_L, "isPrime"); // this pushes the method onto the stack

        lua_pushnumber(_L, static_cast<float>(i)); // this pushes the argument onto the stack

        lua_call(_L, 1, 1); // call the method, expecting one param and one return value

        bool result = static_cast<bool>(lua_toboolean(_L, -1)); // get the result

        if (result) {
            std::cout << i << " true" << std::endl;
        } else {
            std::cout << i << " false" << std::endl;
        }

        lua_pop(_L, 3); // pop the method, argument, and return value off the stack
    }
    lua_close(_L);
}

int main() {
  //setenv("MESA_GL_VERSION_OVERRIDE", "3.2", true);
  //setenv("DISPLAY", "192.168.8.186:0", true);
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "average", average);
  luaL_dofile(L, "avg.lua");
  lua_close(L);
  auto runner = NovelRT::NovelRunner(0, new NovelRT::NovelLayeringService());
  NovelRT::NovelCommonArgs yuriArgs;
  yuriArgs.startingPosition.setX(1920 / 2);
  yuriArgs.startingPosition.setY(1080 / 2);

  runner.getRenderer()->getImageRect("test-yuri.png", yuriArgs);

  auto rectArgs = NovelRT::NovelCommonArgs();
  rectArgs.startingPosition = yuriArgs.startingPosition;
  rectArgs.orderInLayer = 1;

  runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(500, 500), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);
  runner.runNovel();
}