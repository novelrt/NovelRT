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
  public:
    Texture();
    void loadPngAsTexture(const std::string& file);
  };
}

#endif //!NOVELRT_GRAPHICS_TEXTURE_H
