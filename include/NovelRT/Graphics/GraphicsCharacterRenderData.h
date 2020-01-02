// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H
#define NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  struct GraphicsCharacterRenderData {
  public:
    GLuint     textureId;  // ID handle of the glyph texture
    Maths::GeoVector<int> size;       // Size of glyph
    Maths::GeoVector<int> bearing;    // Offset from baseline to left/top of glyph
    AdvanceInteger advance;    // Offset to advance to next glyph
  };
}

#endif //NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H
