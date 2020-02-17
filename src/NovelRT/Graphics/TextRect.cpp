// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include <NovelRT/Graphics/TextRect.h>

namespace NovelRT::Graphics {
  void TextRect::drawObject() {
    for (auto& rect : _letterRects) {
      rect->executeObjectBehaviour();
    }
  }

  void TextRect::setColourConfig(const RGBAConfig& value) {
    _colourConfig = value;
    configureObjectBuffers();
  }

  void TextRect::configureObjectBuffers() {

    if (_previousFontFileDir != _fontFileDir) {
      if (_fontCharacters.size() > 0)
        _fontCharacters.clear();
      FT_Library freeTypeLoader;
      if (FT_Init_FreeType(&freeTypeLoader)) {
        _logger.logErrorLine("Failed to initialise Freetype.");
      }
      FT_Face face;
      if (FT_New_Face(freeTypeLoader, _fontFileDir.c_str(), 0, &face))
        _logger.logError("FREETYPE - Failed to load font: ", _fontFileDir);

      FT_Set_Pixel_Sizes(face, 0, _fontSize);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


      for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
          _logger.logErrorLine("FREETYTPE: Failed to load Glyph");
          continue;
        }
        // Generate texture
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_RED,
          face->glyph->bitmap.width,
          face->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        GraphicsCharacterRenderData character = {
            std::make_shared<Texture>(Texture()),
            Maths::GeoVector<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Maths::GeoVector<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
            GraphicsCharacterRenderDataHelper::getAdvanceDistance(face->glyph->advance.x)
        };
        character.texture->setTextureIdInternal(textureId);
        _fontCharacters.insert(std::pair<GLchar, GraphicsCharacterRenderData>(c, character));
      }
      FT_Done_Face(face);
      FT_Done_FreeType(freeTypeLoader);
      _previousFontFileDir = _fontFileDir;
    }

    reloadText();
  }

  TextRect::TextRect(const Transform& transform,
    int layer,
    ShaderProgram shaderProgram,
    Camera* camera,
    float fontSize,
    const std::string& fontFileDir,
    const RGBAConfig& colourConfig) :
    RenderObject(
      transform,
      layer,
      shaderProgram,
      camera),
    _fontFileDir(fontFileDir),
    _previousFontFileDir(""),
    _text(""),
    _logger(Utilities::Misc::CONSOLE_LOG_GFX),
    _colourConfig(colourConfig),
    _fontSize(fontSize) {}

  std::string TextRect::getText() const {
    return _text;
  }
  void TextRect::setText(const std::string& value) {
    _text = value;
    int difference = _text.length() - _letterRects.size();
    auto modifiedTransform = getTransform();
    modifiedTransform.setScale(Maths::GeoVector<float>(50, 50));
    for (int i = 0; i < difference; i++) {
      auto rect = std::make_unique<ImageRect>(
          modifiedTransform,
          getLayer(),
          _shaderProgram,
          _camera,
          _colourConfig);
      rect->setActive(getActive());
      _letterRects.push_back(std::move(rect));
    }

    if (_bufferInitialised) {
      reloadText();
    }
  }
  void TextRect::reloadText() {

    auto ttfOrigin = getTransform().getPosition();

    int i = 0;
    for (const char& c : getText()) {
      GraphicsCharacterRenderData ch;

      auto match = _fontCharacters.find(c);
      if (match == _fontCharacters.end()) {
        match = _fontCharacters.begin();
      }
      ch = match->second;

      auto currentWorldPosition = Maths::GeoVector<float>((ttfOrigin.getX() + ch.size.getX() / 2.0f) + ch.bearing.getX(),
        (ttfOrigin.getY() - (ch.bearing.getY() / 2.0f))
        + ((ch.size.getY() - ch.bearing.getY()) / 2.0f));

      auto& target = _letterRects.at(i++);
      target->setTextureInternal(ch.texture);
      target->getTransform().setPosition(currentWorldPosition);
      target->getTransform().setScale(Maths::GeoVector<float>(ch.size.getX(), ch.size.getY()));
      target->setActive(true);
      ttfOrigin.setX(ttfOrigin.getX() + (ch.advance >> 6));
    }

    if (_letterRects.size() == static_cast<uint32_t>(i) + 1)
      return;

    auto beginIt = _letterRects.begin() + i;
    auto endIt = _letterRects.end();

    std::for_each(beginIt, endIt, [](const std::unique_ptr<ImageRect>& ptr) {
      ptr->setActive(false);
      });
  }

  void TextRect::setActive(bool value) {
    WorldObject::setActive(value);
    std::for_each(_letterRects.begin(), _letterRects.end(), [&value](auto& x){x->setActive(value);});
  }
}
