// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_TEXTRECT_H
#define NOVELRT_GRAPHICS_TEXTRECT_H

namespace NovelRT::Graphics {
  class TextRect : public RenderObject {
  private:
    void reloadText();

    std::string _fontFileDir;
    std::string _previousFontFileDir = "";
    std::string _text = "";
    std::vector<ImageRect*> _letterRects;
    std::map<GLchar, GraphicsCharacterRenderData> _fontCharacters;
    LoggingService _logger;
    RGBAConfig _colourConfig;
    float _fontSize;

  protected:
    void configureObjectBuffers() final;

  public:
    TextRect(const Transform& transform,
      ShaderProgram programId,
      Camera* camera,
      float fontSize,
      const std::string& fontFileDir,
      const RGBAConfig& colourConfig);

    void drawObject() final;

    RGBAConfig getColourConfig() const;

    void setColourConfig(const RGBAConfig& value);

    std::string getText() const;
    void setText(const std::string& value);
  };
}
#endif //NOVELRT_GRAPHICS_TEXTRECT_H
