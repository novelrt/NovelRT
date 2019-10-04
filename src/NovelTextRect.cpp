// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelTextRect.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace NovelRT {
void NovelTextRect::drawObject() {
  return;
}

RGBAConfig NovelTextRect::getColourConfig() const {
  return _colourConfig;
}

void NovelTextRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
  configureObjectBuffers();
}

void NovelTextRect::configureObjectBuffers() {

  if (_fontCharacters.size() > 0)
    _fontCharacters.clear();

  if (_previousFontFileDir != _fontFileDir) {
    FT_Library freeTypeLoader;
    if (FT_Init_FreeType(&freeTypeLoader)) {
      std::cerr << "ERROR: Failed to initialise Freetype." << std::endl;
    }
    FT_Face face;
    if (FT_New_Face(freeTypeLoader, _fontFileDir.c_str(), 0, &face))
      std::cout << "ERROR: Failed to load font " << _fontFileDir << " via freeType!" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, _fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


    for (GLubyte c = 0; c < 128; c++) {
      // Load character glyph
      if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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
          GeoVector<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          GeoVector<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
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

NovelTextRect::NovelTextRect(NovelLayeringService* layeringService,
                             float fontSize,
                             float screenScale,
                             const std::string& fontFileDir,
                             const RGBAConfig& colourConfig,
                             const NovelCommonArgs& args,
                             GLuint programId) : NovelRenderObject(layeringService,
                                                                         screenScale,
                                                                         GeoVector<float>(200, 200),
                                                                         args,
                                                                         programId), _colourConfig(colourConfig),
                                                       _fontFileDir(fontFileDir), _fontSize(fontSize), _args(args) {

}
std::string NovelTextRect::getText() const {
  return _text;
}
void NovelTextRect::setText(const std::string& value) {
  _text = value;
  int difference = _text.length() - _letterRects.size();
  for (int i = 0; i < difference; i++) {
    _letterRects.push_back(new NovelImageRect(_layeringService,
                                              _screenScale,
                                              GeoVector<float>(50, 50),
                                              _args,
                                              _programId,
                                              _colourConfig));
  }

  if (_bufferInitialised) {
    reloadText();
  }
}
void NovelTextRect::reloadText() {

  auto ttfOrigin = getWorldSpacePosition();

  int i = 0;
  for (const char& c : getText()) {
    GraphicsCharacterRenderData ch;

    auto match = _fontCharacters.find(c);
    if (match == _fontCharacters.end()) {
      match = _fontCharacters.begin();
    }
    ch = match->second;

    auto currentWorldPosition = GeoVector<float>((ttfOrigin.getX() + ch.size.getX() / 2) + ch.bearing.getX(),
                                                 (ttfOrigin.getY() + (ch.bearing.getY() / 2))
                                                     - ((ch.size.getY() - ch.bearing.getY()) / 2));

    auto target = _letterRects[i++];
    target->setTextureInternal(ch.textureId);
    target->setWorldSpacePosition(currentWorldPosition);
    target->setWorldSpaceSize(GeoVector<float>(ch.size.getX(), ch.size.getY()));
    target->setActive(true);
    ttfOrigin.setX(ttfOrigin.getX() + (ch.advance >> 6));
  }

  if (_letterRects.size() == static_cast<uint32_t>(i) + 1)
    return;

  auto beginIt = _letterRects.begin() + i;
  auto endIt = _letterRects.end();

  auto unusedRects = std::vector<NovelImageRect*>(beginIt, endIt);
  for (auto rect : unusedRects) {
    rect->setActive(false);
  }
}
}
