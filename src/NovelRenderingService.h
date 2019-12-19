// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRENDERINGSERVICE_H
#define NOVELRT_NOVELRENDERINGSERVICE_H

#include <SDL2/SDL.h>
#include "GeoVector.h"
#include "NovelCommonArgs.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "RGBAConfig.h"
#include "NovelLoggingService.h"
#include "NovelLayeringService.h"
#include "NovelImageRect.h"
#include "NovelBasicFillRect.h"
#include "NovelTextRect.h"
#include <glad/glad.h>
#include "NovelCamera.h"
#include "ShaderProgram.h"
#include "CameraBlock.h"
#include "NovelWindowingService.h"

namespace NovelRT {

  class NovelRenderingService {
  private:

    bool initialiseRenderPipeline();
    NovelLoggingService _logger;
    NovelLayeringService* const _layeringService;
    NovelWindowingService* const _windowingService;
    SDL_GLContext _openGLContext;

    ShaderProgram loadShaders(std::string vertexFilePath, std::string fragmentFilePath);
    ShaderProgram _basicFillRectProgram;
    ShaderProgram _texturedRectProgram;
    ShaderProgram _fontProgram;

    Lazy<GLuint> _cameraObjectRenderUbo;
    std::unique_ptr<NovelCamera> _camera;

    void bindCameraUboForProgram(GLuint shaderProgramId);

  public:
    NovelRenderingService(NovelLayeringService* const layeringService, NovelWindowingService* const windowingService);
    int initialiseRendering();

    void tearDown() const;

    NovelImageRect* getImageRect(const std::string& filePath,
      const NovelCommonArgs& args,
      const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255));

    NovelBasicFillRect* getBasicFillRect(const RGBAConfig& colourConfig, const NovelCommonArgs& args);

    NovelTextRect* getTextRect(const RGBAConfig& colourConfig,
      float fontSize,
      const std::string& fontFilePath,
      const NovelCommonArgs& args);

    NovelCamera* getCamera() const;

    void beginFrame() const;
    void endFrame() const;
  };

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
