// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#define NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtBasicFillRect* NrtBasicFillRectHandle;
    typedef struct NrtCamera* NrtCameraHandle;
    typedef struct NrtFontSet* NrtFontSetHandle;
    typedef struct NrtImageRect* NrtImageRectHandle;
    typedef struct NrtRenderObject* NrtRenderObjectHandle;
    typedef struct NrtRenderingService* NrtRenderingServiceHandle;
    typedef struct NrtRGBAConfig* NrtRGBAConfigHandle;
    typedef struct NrtTextRect* NrtTextRectHandle;
    typedef struct NrtTexture* NrtTextureHandle;

    typedef enum
    {
        NRT_UNMODIFIED = 0,
        NRT_MODIFIEDINCURRENT = 1,
        NRT_MODIFIEDINLAST = 2
    } NrtCameraFrameStateKind;

    typedef int32_t NrtCameraFrameState;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
