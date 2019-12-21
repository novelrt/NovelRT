// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H
#define NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H

#include <glad.h>
#include "../Maths/GeoVector.h"

namespace NovelRT::Graphics {
typedef std::conditional<sizeof(signed long) <= 4, GLuint, GLuint64>::type AdvanceInteger;
struct GraphicsCharacterRenderData {
public:
  GLuint     textureId;  // ID handle of the glyph texture
  GeoVector<int> size;       // Size of glyph
  GeoVector<int> bearing;    // Offset from baseline to left/top of glyph
  AdvanceInteger advance;    // Offset to advance to next glyph
};
}

#endif //NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H
