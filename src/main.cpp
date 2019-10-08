// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelRenderingService.h"
#include "NovelRunner.h"
#include "NovelImageRect.h"
#include "NovelCommonArgs.h"
#include "NovelLayeringService.h"
#include "NovelInteractionService.h"
#include "NovelAudioService.h"

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
NovelRT::NovelBasicFillRect* basicFillRect2;


int main(int argc, char* argv[]) {
  //setenv("DISPLAY", "localhost:0", true);
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "average", average);
  luaL_dofile(L, "avg.lua");
  lua_close(L);
  auto runner = NovelRT::NovelRunner(0, new NovelRT::NovelLayeringService());
  NovelRT::NovelCommonArgs novelChanArgs;
  novelChanArgs.layer = 0;
  novelChanArgs.orderInLayer = 0;
  novelChanArgs.startingPosition.setX(1920 / 2);
  novelChanArgs.startingPosition.setY(1080 / 2);

  novelChanRect = runner.getRenderer()->getImageRect(NovelRT::GeoVector<float>(456, 618), "novel-chan.png", novelChanArgs, NovelRT::RGBAConfig(255, 0, 255, 255));

  auto rectArgs = NovelRT::NovelCommonArgs();
  rectArgs.startingPosition = novelChanArgs.startingPosition;
  rectArgs.startingPosition.setX(rectArgs.startingPosition.getX() + 400);
  rectArgs.layer = 0;
  rectArgs.orderInLayer = 1;
  rectArgs.startingRotation = 0.0f;

  //basicFillRect = runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs);
  auto textRect = runner.getRenderer()->getTextRect(NovelRT::RGBAConfig(0, 255, 0, 255), 70, "Gayathri-Regular.ttf", rectArgs);
  textRect->setText("RubyGnomer");
  auto rectArgs2 = NovelRT::NovelCommonArgs();
  rectArgs2.startingPosition = novelChanArgs.startingPosition;
  rectArgs2.startingPosition.setX(rectArgs.startingPosition.getX() - 800);
  rectArgs2.layer = 0;
  rectArgs2.orderInLayer = 1;
  rectArgs2.startingRotation = 0.0f;

  basicFillRect = runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(0, 255, 255, 255), rectArgs2);



  runner.getDebugService()->setIsFpsCounterVisible(true);

  runner.runOnUpdate([](double delta) {
    const float rotationAmount = 45.0f;

    auto rotation = novelChanRect->getRotation();
    rotation += rotationAmount * (float)delta;

    if (rotation > 360.0f)
    {
      rotation -= 360.0f;
    }

    novelChanRect->setRotation(rotation);
  });

  auto novelAudio = runner.getAudioService();

  novelAudio->loadMusic("sparta.wav");
  novelAudio->loadSound("w0nd0ws.wav");
  novelAudio->fadeMusicIn("sparta.wav", -1, 5000);
  novelAudio->setGlobalVolume(0.5);


  auto rect = runner.getInteractionService()->getBasicInteractionRect(NovelRT::GeoVector<float>(200, 200), rectArgs2);

  rect->subscribeToInteracted([&novelAudio]{
      std::cout << "Commencing SFX test..." << std::endl;
      novelAudio->fadeMusicOut(500);
      SDL_Delay(600);
      std::cout << "Looping SFX three times." << std::endl;
      novelAudio->playSound("w0nd0ws.wav", 3);
      SDL_Delay(10948);
      std::cout << "Playing SFX in pseudo-5 channel, Front-Right." << std::endl;
      novelAudio->setSoundPosition("w0nd0ws.wav", 45, 127);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "Playing SFX in pseudo-5 channel, Back-Right." << std::endl;
      novelAudio->setSoundPosition("w0nd0ws.wav", 135, 127);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "Playing SFX in pseudo-5 channel, Back-Left." << std::endl;
      novelAudio->setSoundPosition("w0nd0ws.wav", 225, 127);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "Playing SFX in pseudo-5 channel, Front-Left." << std::endl;
      novelAudio->setSoundPosition("w0nd0ws.wav", 315, 127);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "Playing SFX in pseudo-5 channel, Center." << std::endl;
      novelAudio->setSoundPosition("w0nd0ws.wav", 0, 0);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "Playing SFX in Stereo, pan left." << std::endl;
      novelAudio->setSoundPanning("w0nd0ws.wav", 255, 0);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "Playing SFX in Stereo, pan right." << std::endl;
      novelAudio->setSoundPanning("w0nd0ws.wav", 0, 255);
      novelAudio->playSound("w0nd0ws.wav");
      SDL_Delay(4316);
      std::cout << "SFX test complete!" << std::endl;
      novelAudio->playSound("jojo.wav");
      SDL_Delay(7000);
      novelAudio->fadeMusicIn("sparta.wav",0,5000);
    });

  runner.runNovel();

  return 0;
}

