// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_RENDERINGSERVICE_H

namespace NovelRT::Graphics {
  class RenderingService {
  private:
    bool initialiseRenderPipeline();
    LoggingService _logger;
    Windowing::WindowingService* const _windowingService;
    SDL_GLContext _openGLContext;

    ShaderProgram loadShaders(std::string vertexFilePath, std::string fragmentFilePath);
    ShaderProgram _basicFillRectProgram;
    ShaderProgram _texturedRectProgram;
    ShaderProgram _fontProgram;

    Utilities::Lazy<GLuint> _cameraObjectRenderUbo;
    std::unique_ptr<Camera> _camera;

    void bindCameraUboForProgram(GLuint shaderProgramId);

  public:
    RenderingService(Windowing::WindowingService* const windowingService);
    int initialiseRendering();

    void tearDown() const;

    ImageRect* getImageRect(const std::string& filePath, const Transform& transform, const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255));

    BasicFillRect* getBasicFillRect(const RGBAConfig& colourConfig, const Transform& transform);

    TextRect* getTextRect(const RGBAConfig& colourConfig, float fontSize, const std::string& fontFilePath, const Transform& args);

    Camera* getCamera() const;

    void beginFrame() const;
    void endFrame() const;
  };
}
#endif //NOVELRT_GRAPHICS_RENDERINGSERVICE_H
