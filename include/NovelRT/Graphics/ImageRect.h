// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_IMAGERECT_H
#define NOVELRT_GRAPHICS_IMAGERECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class ImageRect : public RenderObject {

  private:
    std::vector<GLfloat> _uvCoordinates;
    std::shared_ptr<Texture> _texture;
    Utilities::Lazy<GLuint> _uvBuffer;
    Utilities::Lazy<GLuint> _colourTintBuffer;
    RGBAConfig _colourTint;
    std::vector<GLfloat> _colourTintData;
    LoggingService _logger;

  protected:
    void configureObjectBuffers() final ;

  public:
    ImageRect(const Transform& transform,
      int layer,
      ShaderProgram shaderProgram,
      std::weak_ptr<Camera> camera,
      std::shared_ptr<Texture> texture,
      const RGBAConfig& colourTint);

    ImageRect(const Transform& transform,
      int layer,
      ShaderProgram shaderProgram,
      std::weak_ptr<Camera> camera,
      const RGBAConfig& colourTint);

    const std::shared_ptr<Texture>& texture() const noexcept {
      return _texture;
    }

    std::shared_ptr<Texture>& texture() noexcept {
      return _texture;
    }

    void drawObject() final ;

    inline const RGBAConfig& colourTint() const {
      return _colourTint;
    }

    inline RGBAConfig& colourTint() {
      _isDirty = true;
      return _colourTint;
    }
  };
}

#endif //NOVELRT_GRAPHICS_IMAGERECT_H
