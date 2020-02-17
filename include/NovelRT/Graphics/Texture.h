#ifndef NOVELRT_GRAPHICS_TEXTURE_H
#define NOVELRT_GRAPHICS_TEXTURE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class Texture {
    friend class ImageRect;
    friend class TextRect;
  private:
    Utilities::Lazy<GLuint> _textureId;
    LoggingService _logger; //not proud of this

    inline GLuint getTextureIdInternal() noexcept {
      return _textureId.getActual();
    }

    inline void setTextureIdInternal(GLuint textureId) noexcept {
      _textureId.reset(textureId);
    }

  public:
    Texture();
    void loadPngAsTexture(const std::string& file);
    ~Texture();
  };
}

#endif //!NOVELRT_GRAPHICS_TEXTURE_H
