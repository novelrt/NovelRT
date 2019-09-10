//
// Created by matth on 27/02/2019.
//

#include <iostream>
#include "NovelTextRect.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace NovelRT {
void NovelTextRect::drawObject() const {
  glUseProgram(_programId);
  //std::cout << glGetError() << std::endl;
  auto colourConfig = getColourConfig();
  glUniform3f(glGetUniformLocation(_programId, "textColour"), colourConfig.getRScalar(), colourConfig.getGScalar(), colourConfig.getBScalar());
  glActiveTexture(GL_TEXTURE0);

  auto surfaceSpace = GeoVector<GLfloat>(_vertexBufferData[0], _vertexBufferData[1]);
  float scale = getScaleHypotenuseScalar();

  for(const char& c : getText()) {
    GraphicsCharacterRenderData ch;

    //std::cout << c << std::endl;

    auto match = _fontCharacters.find(c);
    if (match == _fontCharacters.end())
    {
      match = _fontCharacters.begin();
    }
    ch = match->second;

    GLfloat xpos = surfaceSpace.getX() + ch.bearing.getX() * scale;
    GLfloat ypos = surfaceSpace.getY() - (ch.size.getY() - ch.size.getY()) * scale;

    GLfloat w = ch.size.getX() * scale;
    GLfloat h = ch.size.getY() * scale;
    // Update VBO for each character
    GLfloat vertices[6][4] = {
        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos,     ypos,       0.0, 1.0 },
        { xpos + w, ypos,       1.0, 1.0 },

        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos + w, ypos,       1.0, 1.0 },
        { xpos + w, ypos + h,   1.0, 0.0 }
    };
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureId);



    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, _textBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    surfaceSpace.setX(surfaceSpace.getX() + (ch.advance >> 6) * scale); // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

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
    FT_Library freeTypeLoader;
    if(FT_Init_FreeType(&freeTypeLoader)) {
      std::cerr << "ERROR: Failed to initialise Freetype." << std::endl;
    }
    FT_Face face;
    if (FT_New_Face(freeTypeLoader, _fontFileDir.c_str(), 0, &face)) std::cout << "ERROR: Failed to load font " << _fontFileDir << " via freeType!" << std::endl;

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
          static_cast<AdvanceInteger>(face->glyph->advance.x)
      };
      _fontCharacters.insert(std::pair<GLchar, GraphicsCharacterRenderData>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(freeTypeLoader);

    glGenBuffers(1, &_textBuffer);
  }
}

NovelTextRect::NovelTextRect(NovelLayeringService* layeringService,
                             const float fontSize,
                             const float screenScale,
                             const std::string& fontFileDir,
                             const RGBAConfig& colourConfig,
                             const NovelCommonArgs& args,
                             const GLuint programId) : NovelRenderObject(layeringService,
                                                                         screenScale,
                                                                         GeoVector<float>(0, 0),
                                                                         args,
                                                                         programId), _colourConfig(colourConfig),
                                                       _fontFileDir(fontFileDir), _fontSize(fontSize) {

}
std::string NovelTextRect::getText() const {
  return _text;
}
void NovelTextRect::setText(const std::string& value) {
  _text = value;
}
}