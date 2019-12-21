// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_RENDERINGSERVICE_H

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
#include "BasicFillRect.h"
#include "TextRect.h"
#include <glad/glad.h>
#include "NovelCamera.h"
#include "ShaderProgram.h"
#include "CameraBlock.h"
#include "../Windowing/NovelWindowingService.h"

namespace NovelRT::Graphics {

  class RenderingService {
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
    std::unique_ptr<Camera> _camera;

    void bindCameraUboForProgram(GLuint shaderProgramId);

  public:
    RenderingService(NovelLayeringService* const layeringService, NovelWindowingService* const windowingService);
    int initialiseRendering();

    void tearDown() const;

    ImageRect* getImageRect(const std::string& filePath,
      const CommonArgs& args,
      const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255));

    BasicFillRect* getBasicFillRect(const RGBAConfig& colourConfig, const CommonArgs& args);

    TextRect* getTextRect(const RGBAConfig& colourConfig,
      float fontSize,
      const std::string& fontFilePath,
      const CommonArgs& args);

    Camera* getCamera() const;

    void beginFrame() const;
    void endFrame() const;
  };

}
#endif //NOVELRT_GRAPHICS_RENDERINGSERVICE_H
