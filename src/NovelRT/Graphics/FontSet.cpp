// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  FontSet::FontSet(NovelRunner* runner, Atom id) noexcept :
    _id(0),
    _fontFile("") {

  }

  void FontSet::loadFontAsTexture(const std::string& file, float fontSize) {
    if (!_fontFile.empty()) {
      _logger.logErrorLine("This FontSet has already been initialised with data. Please make a new FontSet!");
      throw std::runtime_error("Unable to continue! Cannot overwrite FontSet!");
      }

      if (_fontCharacters.size() != 0) _fontCharacters.clear();
      FT_Library freeTypeLoader;
      if (FT_Init_FreeType(&freeTypeLoader)) {
        _logger.logErrorLine("Failed to initialise Freetype.");
      }
      FT_Face face;
      if (FT_New_Face(freeTypeLoader, file.c_str(), 0, &face))
        _logger.logError("FREETYPE - Failed to load font: ", file);

      FT_Set_Pixel_Sizes(face, 0, fontSize);

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
            _runner->getRenderer()->getTexture(),
            Maths::GeoVector<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Maths::GeoVector<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
            GraphicsCharacterRenderDataHelper::getAdvanceDistance(face->glyph->advance.x)
        };
        character.texture->setTextureIdInternal(textureId);
        _fontCharacters.insert(std::pair<GLchar, GraphicsCharacterRenderData>(c, character));
      }
      FT_Done_Face(face);
      FT_Done_FreeType(freeTypeLoader);
      _fontFile = file;
    
  }

  FontSet::~FontSet() {
    _runner->getRenderer()->handleFontSetPreDestruction(this);
  }
}
