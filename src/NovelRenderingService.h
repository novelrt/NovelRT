// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

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
#include "NovelTextRect.h"
#include <glad/glad.h>
#include "NovelCamera.h"

namespace NovelRT {

  class NovelRenderingService {
  private:

    struct CameraBlock {
      glm::mat4 cameraMatrix;
      CameraBlock(glm::mat4 matrix) {
        cameraMatrix = matrix;
      }
    };

    bool initializeRenderPipeline(int displayNumber);

    NovelLayeringService* _layeringService;
    std::shared_ptr<SDL_Window> _window;
    SDL_GLContext _openGLContext;

    int _winWidth;
    int _winHeight;

    GLuint loadShaders(std::string vertexFilePath, std::string fragmentFilePath);
    GLuint _basicFillRectProgramId;
    GLuint _texturedRectProgramId;
    GLuint _fontProgramId;

    GeoVector<uint32_t> _screenSize;
    Lazy<GLuint> _cameraObjectRenderUbo;
    Lazy<CameraBlock> _cameraBlockObj;
    NovelCamera _camera;

    void pushUboToGPU(GLuint shaderProgramId);
    CameraBlock generateCameraBlock();

  public:
    NovelRenderingService(NovelLayeringService* layeringService);
    int initialiseRendering(int displayNumber);

    void tearDown() const;

    NovelImageRect* getImageRect(const GeoVector<float>& startingSize,
      std::string_view filePath,
      const NovelCommonArgs& args,
      const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255));
    NovelBasicFillRect* getBasicFillRect(const GeoVector<float>& startingSize,
      const RGBAConfig& colourConfig,
      const NovelCommonArgs& args);
    NovelTextRect* getTextRect(const RGBAConfig& colourConfig,
      float fontSize,
      const std::string& fontFilePath,
      const NovelCommonArgs& args);

    GeoVector<uint32_t> getScreenSize() const;

    void beginFrame() const;
    void endFrame() const;

    std::shared_ptr<SDL_Window> getWindow() const;
  };

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
