// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelWindowingService.h"
#include "NovelUtilities.h"

namespace NovelRT {
  NovelWindowingService::NovelWindowingService() : _window(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(nullptr, SDL_DestroyWindow)){}

  void NovelWindowingService::initialiseWindow(int displayNumber, const std::string& windowTitle) {
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
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    _window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(window, SDL_DestroyWindow);
    _windowSize = GeoVector<float>(wData, hData);

    if (_window == nullptr) {
      _logger.logError("Could not create window: ", std::string(SDL_GetError()));
      throw std::runtime_error("Unable to continue! Window could not be created.");
    }
  }
  void NovelWindowingService::tearDown() {
    SDL_DestroyWindow(getWindow());
    SDL_Quit();
  }
}
