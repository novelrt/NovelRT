// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_IMAGERECT_H
#define NOVELRT_GRAPHICS_IMAGERECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class ImageRect : public RenderObject {
    friend class TextRect;

  private:
    std::string _imageDir;
    std::string _previousImageDir;
    Utilities::Lazy<GLuint> _textureId;
    std::vector<GLfloat> _uvCoordinates;
    Utilities::Lazy<GLuint> _uvBuffer;
    Utilities::Lazy<GLuint> _colourTintBuffer;
    RGBAConfig _colourTint;
    std::vector<GLfloat> _colourTintData;
    LoggingService _logger;

    void setTextureInternal(GLuint textureId);

  protected:
    void configureObjectBuffers() final;

  public:
    ImageRect(const Transform& transform,
      int layer,
      ShaderProgram shaderProgram,
      Camera* camera,
      const std::string& imageDir,
      const RGBAConfig& colourTint);

    ImageRect(const Transform& transform,
      int layer,
      ShaderProgram shaderProgram,
      Camera* camera,
      const RGBAConfig& colourTint);

    void drawObject() final;

    const RGBAConfig& getColourTintConfig() const;
    RGBAConfig& getColourTintConfig();
    void setColourTintConfig(const RGBAConfig& value);
    ~ImageRect() override;
  };
}

#endif //NOVELRT_GRAPHICS_IMAGERECT_H
