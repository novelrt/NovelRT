#ifndef NOVELRT_GRAPHICS_TEXTURE_H
#define NOVELRT_GRAPHICS_TEXTURE_H

namespace NovelRT::Graphics {
  class Texture {
    friend class ImageRect;
    friend class TextRect;
    friend class RenderingService;
    friend class FontSet;
  private:
    Atom _id;
    std::weak_ptr<RenderingService> _renderer;
    Utilities::Lazy<GLuint> _textureId;
    LoggingService _logger; //not proud of this
    std::string _textureFile;
    Maths::GeoVector2<float> _size;

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
    Texture(std::weak_ptr<RenderingService> renderer, Atom id);
    void loadPngAsTexture(const std::string& file);

    inline const std::string& getTextureFile() const noexcept {
      return _textureFile;
    }

    inline const Maths::GeoVector2<float>& getSize() const noexcept {
      return _size;
    }

    ~Texture();
  };
}

#endif //!NOVELRT_GRAPHICS_TEXTURE_H
