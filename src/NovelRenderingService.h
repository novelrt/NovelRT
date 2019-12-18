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

namespace NovelRT {

  class NovelRenderingService {
  private:

    bool initializeRenderPipeline(int displayNumber, const std::string& windowTitle);
    NovelLoggingService _logger;
    NovelLayeringService* _layeringService;
    std::shared_ptr<SDL_Window> _window;
    SDL_GLContext _openGLContext;

    int _winWidth;
    int _winHeight;

    ShaderProgram loadShaders(std::string vertexFilePath, std::string fragmentFilePath);
    ShaderProgram _basicFillRectProgram;
    ShaderProgram _texturedRectProgram;
    ShaderProgram _fontProgram;

    GeoVector<float> _screenSize;
    Lazy<GLuint> _cameraObjectRenderUbo;
    std::unique_ptr<NovelCamera> _camera;

    void bindCameraUboForProgram(GLuint shaderProgramId);

  public:
    NovelRenderingService(NovelLayeringService* layeringService);
    int initialiseRendering(int displayNumber, const std::string& windowTitle);


    std::string getWindowTitle() const;
    void setWindowTitle(const std::string& value);

    void tearDown() const;

    NovelImageRect* getImageRect(const std::string& filePath,
      const NovelCommonArgs& args,
      const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255));

    NovelBasicFillRect* getBasicFillRect(const RGBAConfig& colourConfig, const NovelCommonArgs& args);

    NovelTextRect* getTextRect(const RGBAConfig& colourConfig,
      float fontSize,
      const std::string& fontFilePath,
      const NovelCommonArgs& args);

    GeoVector<float> getScreenSize() const;

    NovelCamera* getCamera() const;

    void beginFrame() const;
    void endFrame() const;

    std::shared_ptr<SDL_Window> getWindow() const;
  };

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
