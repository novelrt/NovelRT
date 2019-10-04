// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICSCHARACTERRENDERDATA_H
#define NOVELRT_GRAPHICSCHARACTERRENDERDATA_H

#include <glad.h>
#include "GeoVector.h"

namespace NovelRT {
typedef std::conditional<sizeof(signed long) <= 4, GLuint, GLuint64>::type AdvanceInteger;
struct GraphicsCharacterRenderData {
public:
  GLuint     textureId;  // ID handle of the glyph texture
  GeoVector<int> size;       // Size of glyph
  GeoVector<int> bearing;    // Offset from baseline to left/top of glyph
  AdvanceInteger advance;    // Offset to advance to next glyph
};
}

#endif //NOVELRT_GRAPHICSCHARACTERRENDERDATA_H
