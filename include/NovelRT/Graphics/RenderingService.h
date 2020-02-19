// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_RENDERINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class RenderingService {
    friend class ImageRect;
    friend class TextRect;
    friend class Texture;
    friend class FontSet;
  private:
    static std::atomic_uintptr_t _nextId;
    bool initialiseRenderPipeline(bool completeLaunch = true, Maths::GeoVector<float>* const optionalWindowSize = nullptr);
    LoggingService _logger;
    NovelRunner* const _runner;

    ShaderProgram loadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ShaderProgram _basicFillRectProgram;
    ShaderProgram _texturedRectProgram;
    ShaderProgram _fontProgram;

    Utilities::Lazy<GLuint> _cameraObjectRenderUbo;
    std::unique_ptr<Camera> _camera;

    std::map<Atom, std::weak_ptr<Texture>> _textureCache;
    std::map<Atom, std::weak_ptr<FontSet>> _fontCache;

    void bindCameraUboForProgram(GLuint shaderProgramId);

    void handleTexturePreDestruction(Texture* target);
    void handleFontSetPreDestruction(FontSet* target);

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

    std::shared_ptr<Texture> getTexture(const std::string& fileTarget = "");
    std::shared_ptr<FontSet> getFontSet(const std::string& fileTarget, float fontSize);
  };
}

#endif //NOVELRT_GRAPHICS_RENDERINGSERVICE_H
