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
    void configureObjectBuffers() final;

  public:
    ImageRect(const Transform& transform,
      int layer,
      ShaderProgram shaderProgram,
      Camera* camera,
      std::shared_ptr<Texture> texture,
      const RGBAConfig& colourTint);

    ImageRect(const Transform& transform,
      int layer,
      ShaderProgram shaderProgram,
      Camera* camera,
      const RGBAConfig& colourTint);

    void setTexture(std::shared_ptr<Texture> texture);

    void drawObject() final;

    const RGBAConfig& getColourTintConfig() const;
    RGBAConfig& getColourTintConfig();
    void setColourTintConfig(const RGBAConfig& value);
  };
}

#endif //NOVELRT_GRAPHICS_IMAGERECT_H
