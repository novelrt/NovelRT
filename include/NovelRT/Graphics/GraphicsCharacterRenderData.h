// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H
#define NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  struct GraphicsCharacterRenderData {
  public:
    std::shared_ptr<Texture> texture;  // ID handle of the glyph texture
    uint32_t sizeX;       // Size of glyph
    uint32_t sizeY;       // Size of glyph
    int32_t bearingX;    // Offset from baseline to left/top of glyph
    int32_t bearingY;    // Offset from baseline to left/top of glyph
    int32_t advance;    // Offset to advance to next glyph
  };
}

#endif //NOVELRT_GRAPHICS_CHARACTERRENDERDATA_H
