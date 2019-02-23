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

namespace NovelRT {
class NovelObject;
class NovelImageRect;
class NovelBasicFillRect;

class NovelRenderingService {
public:
  NovelRenderingService();
  int initialiseRendering(const int displayNumber);

  void updateRenderingLayerInfo(const int layer, NovelObject* targetObject, const bool migrate = true);
  void sortLayerOrder(const int layer);

  NVGcontext* getNanoVGContext() const;

  void renderAllObjects() const;

  void tearDown() const;

  NovelImageRect getImageRect(const std::string_view filePath, const NovelCommonArgs& args);
  NovelBasicFillRect getBasicFillRect(const GeoVector<float>& startingSize, const NovelCommonArgs& args);

  std::shared_ptr<SDL_Window> getWindow() const;

  ~NovelRenderingService();

private:
  bool nanovgInit();

  bool sdlInit(const int displayNumber);

  std::shared_ptr<SDL_Window> _window;
  std::unique_ptr<NVGcontext, void(*)(NVGcontext*)> _nanovgContext;
  SDL_GLContext _openGLContext;
  std::map<int, std::vector<NovelObject*>> _renderObjects;
  float _screenScale;

  int _winWidth;
  int _winHeight;
  int _frameBufferWidth;
  float _pxRatio;
};

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
