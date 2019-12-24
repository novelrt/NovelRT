// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include <NovelRT.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace NovelRT::Graphics {
  void TextRect::drawObject() {
    return;
  }

  RGBAConfig TextRect::getColourConfig() const {
    return _colourConfig;
  }

  void TextRect::setColourConfig(const RGBAConfig& value) {
    _colourConfig = value;
    configureObjectBuffers();
  }

  void TextRect::configureObjectBuffers() {

    if (_fontCharacters.size() > 0)
      _fontCharacters.clear();

    if (_previousFontFileDir != _fontFileDir) {
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
            textureId,
            Maths::GeoVector<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Maths::GeoVector<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<AdvanceInteger>(face->glyph->advance.x)
        };
        _fontCharacters.insert(std::pair<GLchar, GraphicsCharacterRenderData>(c, character));
      }
      FT_Done_Face(face);
      FT_Done_FreeType(freeTypeLoader);
      _previousFontFileDir = _fontFileDir;
    }

    reloadText();
  }

  TextRect::TextRect(const Utilities::CommonArgs& args,
    ShaderProgram shaderProgram,
    Camera* camera,
    float fontSize,
    const std::string& fontFileDir,
    const RGBAConfig& colourConfig) :
    RenderObject(
      args,
      shaderProgram,
      camera),
    _fontFileDir(fontFileDir),
    _args(args),
    _colourConfig(colourConfig),
    _fontSize(fontSize),
    _logger(Utilities::Misc::CONSOLE_LOG_GFX) {}

  std::string TextRect::getText() const {
    return _text;
  }
  void TextRect::setText(const std::string& value) {
    _text = value;
    int difference = _text.length() - _letterRects.size();
    auto modifiedArgs = _args;
    modifiedArgs.startingScale = Maths::GeoVector<float>(50, 50);
    for (int i = 0; i < difference; i++) {
      _letterRects.push_back(new ImageRect(
        _args,
        _shaderProgram,
        _camera,
        _colourConfig));
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

      auto target = _letterRects[i++];
      target->setTextureInternal(ch.textureId);
      target->getTransform().setPosition(currentWorldPosition);
      target->getTransform().setScale(Maths::GeoVector<float>(ch.size.getX(), ch.size.getY()));
      target->setActive(true);
      ttfOrigin.setX(ttfOrigin.getX() + (ch.advance >> 6));
    }

    if (_letterRects.size() == static_cast<uint32_t>(i) + 1)
      return;

    auto beginIt = _letterRects.begin() + i;
    auto endIt = _letterRects.end();

    auto unusedRects = std::vector<ImageRect*>(beginIt, endIt);
    for (auto rect : unusedRects) {
      rect->setActive(false);
    }
  }
}
