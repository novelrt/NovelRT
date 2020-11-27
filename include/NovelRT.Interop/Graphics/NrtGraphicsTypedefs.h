// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#define NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct RenderObjectHandle* NrtRenderObject;
  typedef struct RenderingServiceHandle* NrtRenderingService;
  typedef struct TextureHandle* NrtTexture;
  typedef struct FontSetHandle* NrtFontSet;
  typedef struct BasicFillRectHandle* NrtBasicFillRect;
  typedef struct ImageRectHandle* NrtImageRect;
  typedef struct TextRectHandle* NrtTextRect;
  typedef struct CameraHandle* NrtCamera;

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H