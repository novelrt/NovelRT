// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_GRAPHICS_FONTSET_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class FontSet {
    friend class ImageRect;
    friend class TextRect;
    friend class RenderingService;
  private:
    Atom _id;
    float _fontSize;
    NovelRunner* _runner;
    std::vector<GraphicsCharacterRenderData> _characters;
    LoggingService _logger; //not proud of this
    std::string _fontFile;
    std::map<GLchar, GraphicsCharacterRenderData> _fontCharacters;



    inline const std::vector<GraphicsCharacterRenderData>& getTextureIdInternal() const noexcept {
      return _characters;
    }

    inline Atom getId() const noexcept {
      return _id;
    }

    inline GraphicsCharacterRenderData getCharacterBasedonGLchar(char c) const {
      auto match = _fontCharacters.find(c);
      if (match == _fontCharacters.end()) {
        match = _fontCharacters.begin();
      }

      if (match == _fontCharacters.end()) {
        throw std::runtime_error("Unable to continue! Unable to return specified character.");
      }

      return match->second;
    }

  public:
    FontSet(NovelRunner* runner, Atom id) noexcept;

    void loadFontAsTextureSet(const std::string& file, float fontSize);

    inline std::string getFontFile() const noexcept {
      return _fontFile;
    }

    inline float getFontSize() const noexcept {
      return _fontSize;
    }

    ~FontSet();
  };
}

#endif //!NOVELRT_GRAPHICS_FONTSET_H
