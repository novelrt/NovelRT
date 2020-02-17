#ifndef NOVELRT_GRAPHICS_TEXTURE_H
#define NOVELRT_GRAPHICS_TEXTURE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class Texture {
    friend class ImageRect;
    friend class TextRect;
    friend class RenderingService;
  private:
    Atom _id;
    NovelRunner* _runner;
    Utilities::Lazy<GLuint> _textureId;
    LoggingService _logger; //not proud of this
    std::string _textureFile;


    inline GLuint getTextureIdInternal() noexcept {
      return _textureId.getActual();
    }

    inline void setTextureIdInternal(GLuint textureId) noexcept {
      _textureId.reset(textureId);
    }

    inline Atom getId() const noexcept {
      return _id;
    }

  public:
    Texture(NovelRunner* runner, Atom id);
    void loadPngAsTexture(const std::string& file);

    inline std::string getTextureFile() const noexcept {
      return _textureFile;
    }

    ~Texture();
  };
}

#endif //!NOVELRT_GRAPHICS_TEXTURE_H
