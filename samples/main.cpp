// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

//TODO: What do I do with these?
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

lua_State* L;

static int average(lua_State *luaState) {
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

//TODO: Do we really need this anymore? No real reason to run this in WSL these days.
#ifdef WIN32
#define setenv(name, value, overwrite) \
  static_assert(overwrite != 0);       \
  _putenv_s(name, value)
#endif

std::unique_ptr<NovelRT::Graphics::ImageRect> novelChanRect;
std::unique_ptr<NovelRT::Graphics::TextRect> textRect;
std::unique_ptr<NovelRT::Graphics::BasicFillRect> lineRect;
std::unique_ptr<NovelRT::Graphics::BasicFillRect> playAudioButton;
std::unique_ptr<NovelRT::Graphics::BasicFillRect> playAudioButtonTwoElectricBoogaloo;
std::unique_ptr<NovelRT::Graphics::TextRect> playAudioText;
std::unique_ptr<NovelRT::Input::BasicInteractionRect> interactionRect;
std::unique_ptr<NovelRT::Input::BasicInteractionRect> memeInteractionRect;

int main(int argc, char *argv[])
{
  std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
  std::filesystem::path resourcesDirPath = executableDirPath / "Resources";

  std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";
  std::filesystem::path imagesDirPath = resourcesDirPath / "Images";
  std::filesystem::path scriptsDirPath = resourcesDirPath / "Scripts";

  //setenv("DISPLAY", "localhost:0", true);
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "average", average);
  luaL_dofile(L, (scriptsDirPath / "avg.lua").string().c_str());
  lua_close(L);
  auto runner = NovelRT::NovelRunner(0, "NovelRTTest");
  auto console = NovelRT::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_APP);

  auto novelChanTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(1920 / 2, 1080 / 2), 2, NovelRT::Maths::GeoVector<float>(456, 618));

  novelChanRect = runner.getRenderer()->createImageRect(novelChanTransform, 3, (imagesDirPath / "novel-chan.png").string(), NovelRT::Graphics::RGBAConfig(255, 0, 255, 255));

  auto rubyGnomerTextTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(novelChanTransform.getPosition().getX() + 400, novelChanTransform.getPosition().getY()), 0, NovelRT::Maths::GeoVector<float>(1.0f, 1.0f));

  textRect = runner.getRenderer()->createTextRect(rubyGnomerTextTransform, 2, NovelRT::Graphics::RGBAConfig(0, 255, 0, 255), 70, (fontsDirPath / "Gayathri-Regular.ttf").string());
  textRect->setText("RubyGnomer");

  auto lineTransform = NovelRT::Transform(rubyGnomerTextTransform.getPosition(), 0, NovelRT::Maths::GeoVector<float>(1000.0f, 2.0f));

  lineRect = runner.getRenderer()->createBasicFillRect(lineTransform, 1, NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));

  auto playButtonTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(novelChanTransform.getPosition().getX() - 500, novelChanTransform.getPosition().getY()), 0, NovelRT::Maths::GeoVector<float>(200, 200));
  playAudioButton = runner.getRenderer()->createBasicFillRect(playButtonTransform, 3, NovelRT::Graphics::RGBAConfig(255, 0, 0, 70));
  auto playAudioTextTransform = playButtonTransform;
  playAudioTextTransform.setScale(NovelRT::Maths::GeoVector<float>(1.0f, 1.0f));
  auto vec = playButtonTransform.getPosition();
  vec.setX(playButtonTransform.getPosition().getX() - 75);
  playAudioTextTransform.setPosition(vec);
  playAudioText = runner.getRenderer()->createTextRect(playAudioTextTransform, 1, NovelRT::Graphics::RGBAConfig(0, 0, 0, 255), 36, (fontsDirPath / "Gayathri-Regular.ttf").string());
  playAudioText->setText("Play Audio");

  auto theRealMvpTransform = playButtonTransform;
  auto whatever = playButtonTransform.getPosition();
  whatever.setX(whatever.getX() + 50);
  theRealMvpTransform.setPosition(whatever);

  memeInteractionRect = runner.getInteractionService()->createBasicInteractionRect(theRealMvpTransform, -1);

  playAudioButtonTwoElectricBoogaloo = runner.getRenderer()->createBasicFillRect(theRealMvpTransform, 2, NovelRT::Graphics::RGBAConfig(0, 255, 0, 70));


  runner.getDebugService()->setIsFpsCounterVisible(true);

  runner.runOnUpdate([](double delta) {
    const float rotationAmount = 45.0f;

    auto rotation = novelChanRect->getTransform().getRotation();
    rotation += rotationAmount * (float)delta;
    novelChanRect->getTransform().setRotation(rotation);

    if (rotation > 360.0f)
    {
      rotation -= 360.0f;
    }

    novelChanRect->getTransform().setRotation(rotation);
  });

  auto novelAudio = runner.getAudioService();

  novelAudio->load("sparta.wav", true);
  novelAudio->load("w0nd0ws.wav", false);
  novelAudio->fadeMusicIn("sparta.wav", -1, 5000);
  novelAudio->setGlobalVolume(0.5);

  interactionRect = runner.getInteractionService()->createBasicInteractionRect(playButtonTransform, 2);
  auto counter = 0;
  auto loggingLevel = NovelRT::LogLevel::Debug;

  memeInteractionRect->subscribeToInteracted([&console] {
    console.logDebug("WAHEYYY");
    });

  interactionRect->subscribeToInteracted([&novelAudio, &counter, &loggingLevel, &console, &runner] {
    counter++;
    console.log("Test button!", loggingLevel);
    switch (counter) {
      case 1:
        novelAudio->fadeMusicOut(500);
        console.logInternal("Commencing Audio Test...", loggingLevel);
        console.logInternal("Press the button to launch each test.", loggingLevel);
        console.logInternal("(Please wait for each test to finish for best results!)", loggingLevel);
        break;
      case 2:
        console.logInternal("Looping 3 times...", loggingLevel);
        novelAudio->playSound("w0nd0ws.wav", 3);
        break;
      case 3:
        console.logInternal("Pan Left (via Panning)...", loggingLevel);
        novelAudio->setSoundPanning("w0nd0ws.wav", 255, 0);
        novelAudio->playSound("w0nd0ws.wav", 0);
        break;
      case 4:
        console.logInternal("Pan Right (via 3D Position)...", loggingLevel);
        novelAudio->setSoundPosition("w0nd0ws.wav", 90, 127);
        novelAudio->playSound("w0nd0ws.wav", 0);
        break;
      case 5:
        novelAudio->setSoundPosition("w0nd0ws.wav", 0, 0);
        console.logInternal("Low Volume...", loggingLevel);
        novelAudio->setSoundVolume("w0nd0ws.wav", 0.25);
        novelAudio->playSound("w0nd0ws.wav", 0);
        break;
      case 6:
        novelAudio->setSoundVolume("w0nd0ws.wav", 0.5);
        console.logInternal("Success! Click once more to play music again.", loggingLevel);
        novelAudio->setSoundVolume("w0nd0ws.wav", 64);
        novelAudio->playSound("jojo.wav", 0);
        break;
      default:
        counter = 0;
        novelAudio->fadeMusicIn("sparta.wav", -1, 500);
        break;
    }
  });

  runner.subscribeToSceneConstructionRequested([] {


    playAudioButton->executeObjectBehaviour();

    playAudioButtonTwoElectricBoogaloo->executeObjectBehaviour();

    playAudioText->executeObjectBehaviour();


    memeInteractionRect->executeObjectBehaviour();


    interactionRect->executeObjectBehaviour();

    novelChanRect->executeObjectBehaviour();
    textRect->executeObjectBehaviour();
    lineRect->executeObjectBehaviour();
    });

  runner.runNovel();

  return 0;
}
