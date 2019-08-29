//
// Created by matth on 19/12/2018.
//

#ifndef NOVELRT_NOVELRENDERINGSERVICE_H
#define NOVELRT_NOVELRENDERINGSERVICE_H

#include <SDL2/SDL.h>
#include "GeoVector.h"
#include "NovelCommonArgs.h"
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "RGBAConfig.h"
#include "NovelLayeringService.h"
#include "NovelImageRect.h"
#include "NovelBasicFillRect.h"
#include <glad/glad.h>

namespace NovelRT {

class NovelRenderingService {
public:
  NovelRenderingService(NovelLayeringService* layeringService);
  int initialiseRendering(const int displayNumber);

  void tearDown() const;

  NovelImageRect* getImageRect(const GeoVector<float>& startingSize, 
                               const std::string_view filePath,
                               const NovelCommonArgs& args);
  NovelBasicFillRect* getBasicFillRect(const GeoVector<float>& startingSize,
                                       const RGBAConfig& colourConfig,
                                       const NovelCommonArgs& args);

  float getScreenScale() const;

  void beginFrame() const;
  void endFrame() const;

  std::shared_ptr<SDL_Window> getWindow() const;

private:

  bool initializeRenderPipeline(const int displayNumber);

  NovelLayeringService* _layeringService;
  std::shared_ptr<SDL_Window> _window;
  SDL_GLContext _openGLContext;
  float _screenScale;

  int _winWidth;
  int _winHeight;
  int _frameBufferWidth;

  GLuint loadShaders(std::string vertexFilePath, std::string fragmentFilePath);
  GLuint _basicFillRectProgramId;
  GLuint _texturedRectProgramId;
};

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
