// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Windowing {
  WindowingService::WindowingService(NovelRunner* const runner) :
    _window(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(nullptr, SDL_DestroyWindow)),
    _runner(runner) {
    runner->getInteractionService()->unsubscribeFromResizeInputDetected([this](auto value) {
      _windowSize = value;
      raiseWindowResized(_windowSize); });
  }

  void WindowingService::initialiseWindow(int displayNumber, const std::string& windowTitle) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
      _logger.logError("Could not initialize SDL2: ", std::string(SDL_GetError()));
      throw std::runtime_error("Unable to continue! SDL2 failed to initialise.");
    }

    SDL_DisplayMode displayData;
    SDL_GetCurrentDisplayMode(displayNumber, &displayData);

    // create window
    float wData = displayData.w * 0.7f;
    float hData = displayData.h * 0.7f;
    auto window = SDL_CreateWindow(
      windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    _window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(window, SDL_DestroyWindow);
    _windowSize = Maths::GeoVector<float>(wData, hData);

    if (_window == nullptr) {
      _logger.logError("Could not create window: ", std::string(SDL_GetError()));
      throw std::runtime_error("Unable to continue! Window could not be created.");
    }
  }
  void WindowingService::tearDown() {
    raiseWindowClosed();
    SDL_DestroyWindow(getWindow());
    SDL_Quit();
  }
}
