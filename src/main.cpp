// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelLoggingService.h"
#include "NovelRenderingService.h"
#include "NovelRunner.h"
#include "NovelImageRect.h"
#include "NovelCommonArgs.h"
#include "NovelLayeringService.h"
#include "NovelInteractionService.h"
#include "NovelAudioService.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

lua_State *L;

static int average(lua_State *luaState)
{
  int n = lua_gettop(luaState);
  double sum = 0;
  for (int i = 1; i <= n; i++)
  {
    sum += lua_tonumber(luaState, i);
  }
  lua_pushnumber(luaState, sum / n);
  lua_pushnumber(luaState, sum);
  return 2;
}

#ifdef WIN32
#define setenv(name, value, overwrite) \
  static_assert(overwrite != 0);       \
  _putenv_s(name, value)
#endif

NovelRT::NovelBasicFillRect *playAudioButton;
NovelRT::NovelImageRect *novelChanRect;

int main(int argc, char *argv[])
{
  //setenv("DISPLAY", "localhost:0", true);
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "average", average);
  luaL_dofile(L, "avg.lua");
  lua_close(L);
  auto runner = NovelRT::NovelRunner(0, new NovelRT::NovelLayeringService());
  auto console = NovelRT::NovelLoggingService::NovelLoggingService(NovelRT::NovelUtilities::CONSOLE_LOG_APP);
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
  rectArgs.orderInLayer = 2;
  rectArgs.startingRotation = 0.0f;

  auto textRect = runner.getRenderer()->getTextRect(NovelRT::RGBAConfig(0, 255, 0, 255), 70, "Gayathri-Regular.ttf", rectArgs);
  textRect->setText("RubyGnomer");

  auto playButtonArgs = NovelRT::NovelCommonArgs();
  playButtonArgs.startingPosition = novelChanArgs.startingPosition;
  playButtonArgs.startingPosition.setX(rectArgs.startingPosition.getX() - 800);
  playButtonArgs.layer = 0;
  playButtonArgs.orderInLayer = 1;
  playButtonArgs.startingRotation = 0.0f;

  playAudioButton = runner.getRenderer()->getBasicFillRect(NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(255, 0, 0, 255), playButtonArgs);
  playButtonArgs.startingPosition.setX(playButtonArgs.startingPosition.getX() - 75);
  playButtonArgs.orderInLayer = 1;
  auto playAudioText = runner.getRenderer()->getTextRect(NovelRT::RGBAConfig(0, 0, 0, 255), 36, "Gayathri-Regular.ttf", playButtonArgs);
  playAudioText->setText("Play Audio");

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

  novelAudio->load("sparta.wav", true);
  novelAudio->load("w0nd0ws.wav", false);
  novelAudio->fadeMusicIn("sparta.wav", -1, 5000);
  novelAudio->setGlobalVolume(0.5);

  auto rect = runner.getInteractionService()->getBasicInteractionRect(NovelRT::GeoVector<float>(200, 200), playButtonArgs);
  auto counter = 0;
  auto loggingLevel = NovelRT::LogLevel::DEBUG;

  rect->subscribeToInteracted([&novelAudio, &counter, &loggingLevel, &console] {
    counter++;
    switch (counter)
    {
      case 1:
      {
        novelAudio->fadeMusicOut(500);
        console.logInternal("Commencing Audio Test...", loggingLevel);
        console.logInternal("Press the button to launch each test.", loggingLevel);
        console.logInternal("(Please wait for each test to finish for best results!)", loggingLevel);
        break;
      }
      case 2:
      {
        console.logInternal("Looping 3 times...", loggingLevel);
        novelAudio->playSound("w0nd0ws.wav", 3);
        break;
      }
      case 3:
      {
        console.logInternal("Pan Left (via Panning)...", loggingLevel);
        novelAudio->setSoundPanning("w0nd0ws.wav", 255, 0);
        novelAudio->playSound("w0nd0ws.wav", 0);
        break;
      }
      case 4:
      {
        console.logInternal("Pan Right (via 3D Position)...", loggingLevel);
        novelAudio->setSoundPosition("w0nd0ws.wav", 90, 127);
        novelAudio->playSound("w0nd0ws.wav", 0);
        break;
      }
      case 5:
      {
        novelAudio->setSoundPosition("w0nd0ws.wav", 0, 0);
        console.logInternal("Low Volume...", loggingLevel);
        novelAudio->setSoundVolume("w0nd0ws.wav", 0.25);
        novelAudio->playSound("w0nd0ws.wav", 0);
        break;
      }
      case 6:
      {
        novelAudio->setSoundVolume("w0nd0ws.wav", 0.5);
        console.logInternal("Success! Click once more to play music again.", loggingLevel);
        novelAudio->setSoundVolume("w0nd0ws.wav", 64);
        novelAudio->playSound("jojo.wav", 0);
        break;
      }
      default:
      {
        counter = 0;
        novelAudio->fadeMusicIn("sparta.wav", -1, 500);
        break;
      }
    }
  });

  runner.runNovel();

  return 0;
}
