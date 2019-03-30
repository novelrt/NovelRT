//
// Created by matth on 19/12/2018.
//

#include "NovelRenderingService.h"

#include "../lib/SDL2/include/SDL.h"
#include <iostream>

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#if OPENGL_VERSION == 3
#define NANOVG_GL3_IMPLEMENTATION
#elif OPENGL_VERSION == 2
#define NANOVG_GL2_IMPLEMENTATION
#endif
#include "../lib/nanovg/nanovg.h"
#include "../lib/nanovg/nanovg_gl.h"
#include "../lib/nanovg/nanovg_gl_utils.h"
#include "GeoVector.h"
#include "NovelBasicFillRect.h"
#include "NovelImageRect.h"
#include <algorithm>

namespace NovelRT {
bool NovelRenderingService::sdlInit(const int displayNumber) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    std::cerr << "could not initialize sdl2: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_DisplayMode displayData;
  SDL_GetCurrentDisplayMode(displayNumber, &displayData);
  _screenScale = (displayData.h * 0.7f) / 1080.0f;

  std::cout << _screenScale << std::endl;


  // create window
  float wData = 1920.0f * _screenScale;
  float hData = 1080.0f * _screenScale;
  _window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
      "NovelRTTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
  if (_window == nullptr) {
    std::cerr << "could not create window: " << SDL_GetError() << std::endl;

    return false;
  }
  _openGLContext = SDL_GL_CreateContext(_window.get());
  SDL_GL_MakeCurrent(_window.get(), _openGLContext);
  return true;
}

bool NovelRenderingService::nanovgInit() {
#if OPENGL_VERSION == 3
  _nanovgContext =
      std::unique_ptr<NVGcontext, void (*)(NVGcontext*)>(nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG),
                                                         &nvgDeleteGL3);
#elif OPENGL_VERSION == 2
  _nanovgContext = std::unique_ptr<NVGcontext, void (*)(NVGcontext*)>(nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG),
                                                         &nvgDeleteGL2);
#endif
  if (_nanovgContext == nullptr) {
    std::cerr << "%llu\n", _nanovgContext.get();
    std::cerr << "Could not init nanovg.\n";
    return false;
  }

  return true;
}

int NovelRenderingService::initialiseRendering(const int displayNumber) {
  if (!sdlInit(displayNumber)) {
    std::cerr << "Apologies, something went wrong. Reason: SDL could not initialise." << std::endl;
    return 1;
  }

  if (!nanovgInit()) {
    std::cerr << "Apologies, something went wrong. Reason: nanovg could not initialise." << std::endl;
    return 1;
  }

  SDL_GetWindowSize(getWindow().get(), &_winWidth, &_winHeight);
  _frameBufferWidth = _winWidth;

  _pxRatio = (float) _frameBufferWidth / (float) _winWidth; //TODO: WTF?

  return 0;
}

void NovelRenderingService::tearDown() const {
  SDL_DestroyWindow(getWindow().get());
  SDL_Quit();
}

void NovelRenderingService::beginFrame() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  nvgBeginFrame(_nanovgContext.get(), _winWidth, _winHeight, _pxRatio);
}

void NovelRenderingService::endFrame() const {
  nvgEndFrame(_nanovgContext.get());
  SDL_GL_SwapWindow(_window.get());
}

NovelImageRect& NovelRenderingService::getImageRect(const std::string_view filePath, const NovelCommonArgs& args) {
  return *new NovelImageRect(_layeringService, _screenScale, filePath, args, this);
}

NVGcontext* NovelRenderingService::getNanoVGContext() const {
  return _nanovgContext.get();

}

std::shared_ptr<SDL_Window> NovelRenderingService::getWindow() const {
  return _window;
}

NovelRenderingService::NovelRenderingService(NovelLayeringService* layeringService) : _nanovgContext(nullptr,
                                                                                                     &nvgDeleteGL3),
                                                                                      _layeringService(layeringService) {
}

NovelBasicFillRect& NovelRenderingService::getBasicFillRect(const GeoVector<float>& startingSize,
                                                            const RGBAConfig& colourConfig,
                                                            const NovelCommonArgs& args) {
  return *new NovelBasicFillRect(_layeringService, _screenScale, startingSize, colourConfig, args, this);
}
}