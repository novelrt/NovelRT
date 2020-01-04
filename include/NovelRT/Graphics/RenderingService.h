// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_RENDERINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class RenderingService {
  private:
    bool initialiseRenderPipeline(bool completeLaunch = true, Maths::GeoVector<float>* const optionalWindowSize = nullptr);
    LoggingService _logger;
    NovelRunner* const _runner;
    SDL_GLContext _openGLContext;

    ShaderProgram loadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ShaderProgram _basicFillRectProgram;
    ShaderProgram _texturedRectProgram;
    ShaderProgram _fontProgram;

    Utilities::Lazy<GLuint> _cameraObjectRenderUbo;
    std::unique_ptr<Camera> _camera;

    void bindCameraUboForProgram(GLuint shaderProgramId);

  public:
    RenderingService(NovelRunner* const runner);
    int initialiseRendering();

    void tearDown() const;

    std::unique_ptr<ImageRect> createImageRect(const Transform& transform, int layer, const std::string& filePath, const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255));

    std::unique_ptr<BasicFillRect> createBasicFillRect(const Transform& transform, int layer, const RGBAConfig& colourConfig);

    std::unique_ptr<TextRect> createTextRect(const Transform& transform, int layer, const RGBAConfig& colourConfig, float fontSize, const std::string& fontFilePath);

    Camera* getCamera() const;

    void beginFrame() const;
    void endFrame() const;
  };
}

#endif //NOVELRT_GRAPHICS_RENDERINGSERVICE_H
