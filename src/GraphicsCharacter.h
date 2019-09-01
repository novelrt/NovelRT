//
// Created by matt on 30/08/2019.
//

#ifndef NOVELRT_GRAPHICSCHARACTER_H
#define NOVELRT_GRAPHICSCHARACTER_H

#include <glad.h>
#include <glm/vec2.hpp>

namespace NovelRT {
struct GraphicsCharacter {
public:
  GLuint     TextureID;  // ID handle of the glyph texture
  glm::ivec2 Size;       // Size of glyph
  glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
  GLuint     Advance;    // Offset to advance to next glyph
};
}

#endif //NOVELRT_GRAPHICSCHARACTER_H
