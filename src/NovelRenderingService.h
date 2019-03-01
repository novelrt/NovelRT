//
// Created by matth on 19/12/2018.
//

#ifndef NOVELRT_NOVELRENDERINGSERVICE_H
#define NOVELRT_NOVELRENDERINGSERVICE_H

#include "../lib/SDL2/include/SDL.h"
#include "../lib/nanovg/nanovg.h"
#include "GeoVector.h"
#include "NovelCommonArgs.h"
#include <vector>
#include <map>
#include <functional>
#include "RGBAConfig.h"
#include "NovelLayeringService.h"

namespace NovelRT {
class NovelObject;
class NovelImageRect;
class NovelBasicFillRect;

class NovelRenderingService {
public:
  NovelRenderingService(NovelLayeringService* layeringService);
  int initialiseRendering(const int displayNumber);

  NVGcontext* getNanoVGContext() const;

  void tearDown() const;

  NovelImageRect& getImageRect(const std::string_view filePath, const NovelCommonArgs& args);
  NovelBasicFillRect& getBasicFillRect(const GeoVector<float>& startingSize,
                                       const RGBAConfig& colourConfig,
                                       const NovelCommonArgs& args);

  void beginFrame() const;
  void endFrame() const;

  std::shared_ptr<SDL_Window> getWindow() const;

private:
  bool nanovgInit();

  bool sdlInit(const int displayNumber);

  NovelLayeringService* _layeringService;
  std::shared_ptr<SDL_Window> _window;
  std::unique_ptr<NVGcontext, void (*)(NVGcontext*)> _nanovgContext;
  SDL_GLContext _openGLContext;
  float _screenScale;

  int _winWidth;
  int _winHeight;
  int _frameBufferWidth;
  float _pxRatio;

};

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
