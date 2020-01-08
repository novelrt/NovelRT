// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_BASICFILLRECT_H
#define NOVELRT_GRAPHICS_BASICFILLRECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class BasicFillRect : public RenderObject {

  private:
    RGBAConfig _colourConfig;
    Utilities::Lazy<GLuint> _colourBuffer;
    std::vector<GLfloat> _colourData;

  protected:
    void configureObjectBuffers() final;

  public:
    BasicFillRect(const Transform& transform,
      int layer,
      Camera* camera,
      ShaderProgram shaderProgram,
      const RGBAConfig& fillColour);

    void drawObject() final;
    const RGBAConfig& getColourConfig() const;
    RGBAConfig& getColourConfig();
    void setColourConfig(const RGBAConfig& value);
  };
}

#endif //NOVELRT_GRAPHICS_BASICFILLRECT_H
