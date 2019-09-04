//
// Created by matth on 27/02/2019.
//

#include <iostream>
#include "NovelTextRect.h"

namespace NovelRT {
void NovelTextRect::drawObject() const {

}

RGBAConfig NovelTextRect::getColourConfig() const {
  return _colourConfig;
}

void NovelTextRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
  configureObjectBuffers();
}
void NovelTextRect::configureObjectBuffers(const bool refreshBuffers) {
  NovelRenderObject::configureObjectBuffers(refreshBuffers);

  if (refreshBuffers) {
    FT_Face face;
    if (FT_New_Face(_freeTypeLoader, _fontFileDir.c_str(), 0, &face)) std::cout << "ERROR: Failed to load font " << _fontFileDir << " via freeType!" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, _fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (GLubyte c = 0; c < 128; c++)
    {
      // Load character glyph
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      {
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
          face->glyph->advance.x
      };
      _fontCharacters.insert(std::pair<GLchar, GraphicsCharacterRenderData>(c, character));
    }

  }
}
NovelTextRect::NovelTextRect(NovelLayeringService* layeringService,
                             const float fontSize,
                             const float screenScale,
                             const std::string& fontFileDir,
                             const RGBAConfig& colourConfig,
                             const FT_Library& freeTypeLoader,
                             const NovelCommonArgs& args,
                             const GLuint programId) : NovelRenderObject(layeringService,
                                                                         screenScale,
                                                                         GeoVector<float>(0, 0),
                                                                         args,
                                                                         programId), _colourConfig(colourConfig),
                                                       _fontFileDir(fontFileDir), _fontSize(fontSize),
                                                       _freeTypeLoader(freeTypeLoader) {

}
}