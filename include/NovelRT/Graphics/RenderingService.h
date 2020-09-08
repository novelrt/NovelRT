// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_RENDERINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class RenderingService : public std::enable_shared_from_this<RenderingService>, public IRenderingService {
    friend class ImageRect;
    friend class TextRect;
    friend class Texture;
    friend class FontSet;
  private:
    bool initialiseRenderPipeline(bool completeLaunch = true, Maths::GeoVector2<float>* const optionalWindowSize = nullptr);
    LoggingService _logger;

    ShaderProgram loadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ShaderProgram _basicFillRectProgram;
    ShaderProgram _texturedRectProgram;
    ShaderProgram _fontProgram;
    
    Utilities::Lazy<GLuint> _cameraObjectRenderUbo;
    std::shared_ptr<Camera> _camera;

    std::map<Atom, std::weak_ptr<Texture>> _textureCache;
    std::map<Atom, std::weak_ptr<FontSet>> _fontCache;

    RGBAConfig _framebufferColour;

    void bindCameraUboForProgram(GLuint shaderProgramId);

    void handleTexturePreDestruction(Texture* target);
    void handleFontSetPreDestruction(FontSet* target);

  public:
    RenderingService(std::shared_ptr<Windowing::WindowingService> windowingService) noexcept;
    int initialiseRendering() override;
    void tearDown() override;

    std::unique_ptr<ImageRect> createImageRect(const Transform& transform, int layer, const std::string& filePath, const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255)) override;

    std::unique_ptr<ImageRect> createImageRect(const Transform& transform, int layer, const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255)) override;

    std::unique_ptr<BasicFillRect> createBasicFillRect(const Transform& transform, int layer, const RGBAConfig& colourConfig) override;

    std::unique_ptr<TextRect> createTextRect(const Transform& transform, int layer, const RGBAConfig& colourConfig, float fontSize, const std::string& fontFilePath) override;

    std::weak_ptr<Camera> getCamera() const override;

    void beginFrame() const override;
    void endFrame() const override;

    void setBackgroundColour(const RGBAConfig& colour) override;

    std::shared_ptr<Texture> getTexture(const std::string& fileTarget = "") override;
    std::shared_ptr<FontSet> getFontSet(const std::string& fileTarget, float fontSize) override;
  };
}

#endif //NOVELRT_GRAPHICS_RENDERINGSERVICE_H
