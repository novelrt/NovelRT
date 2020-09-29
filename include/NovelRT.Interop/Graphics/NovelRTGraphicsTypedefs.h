// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#define NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct RenderingServiceHandle* NovelRTRenderingService;
  typedef struct TextureHandle* NovelRTTexture;
  typedef struct FontSetHandle* NovelRTFontSet;
  typedef struct BasicFillRectHandle* NovelRTBasicFillRect;
  typedef struct ImageRectHandle* NovelRTImageRect;
  typedef struct TextRectHandle* NovelRTTextRect;
  typedef struct CameraHandle* NovelRTCamera;

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H