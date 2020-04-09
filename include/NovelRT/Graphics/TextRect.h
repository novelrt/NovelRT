// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_TEXTRECT_H
#define NOVELRT_GRAPHICS_TEXTRECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class TextRect : public RenderObject {

  private:
    void reloadText() noexcept ;

    std::string _fontFileDir;
    std::string _previousFontFileDir;
    std::string _text;
    std::vector<std::unique_ptr<ImageRect>> _letterRects;
    LoggingService _logger;
    RGBAConfig _colourConfig;
    std::shared_ptr<FontSet> _fontSet;

  protected:
    void configureObjectBuffers() final;

  public:
    TextRect(const Transform& transform,
      int layer,
      ShaderProgram programId,
      std::weak_ptr<Camera> camera,
      std::shared_ptr<FontSet> fontSet,
      const RGBAConfig& colourConfig);

    void drawObject() final;

    inline const RGBAConfig& getColourConfig() const noexcept {
      return _colourConfig;
    }

    inline RGBAConfig& getColourConfig() noexcept {
      return _colourConfig;
    }

    void setColourConfig(const RGBAConfig& value) noexcept ;

    std::string getText() const;
    void setText(const std::string& value) noexcept ;

    void setActive(bool value) override;

    inline std::shared_ptr<FontSet> getFontSet() const noexcept {
      return _fontSet;
    }

    inline void setFontSet(std::shared_ptr<FontSet> value) noexcept {
      _fontSet = value;
    }

  };
}

#endif //NOVELRT_GRAPHICS_TEXTRECT_H
