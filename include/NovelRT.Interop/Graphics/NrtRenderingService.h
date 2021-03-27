// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_RenderingService_create(NrtWindowingServiceHandle windowingService,
                                          NrtRenderingServiceHandle* outputRenderingService);
    NrtResult Nrt_RenderingService_initialiseRendering(
        NrtRenderingServiceHandle renderingService); // this function has its own return codes, so in theory we can combine
                                               // them both into the main return code
    NrtResult Nrt_RenderingService_tearDown(NrtRenderingServiceHandle renderingService);
    NrtResult Nrt_RenderingService_createImageRectWithFile(NrtRenderingServiceHandle renderingService,
                                                           NrtImageRectHandle* outputImageRect,
                                                           NrtTransform transform,
                                                           int32_t layer,
                                                           const char* filePath,
                                                           NrtRGBAConfigHandle colourTint);
    NrtResult Nrt_RenderingService_createImageRectWithNothing(NrtRenderingServiceHandle renderingService,
                                                              NrtImageRectHandle* outputImageRect,
                                                              NrtTransform transform,
                                                              int32_t layer,
                                                              NrtRGBAConfigHandle colourTint);
    NrtResult Nrt_RenderingService_createBasicFillRect(NrtRenderingServiceHandle renderingService,
                                                       NrtBasicFillRectHandle* outputBasicFillRect,
                                                       NrtTransform transform,
                                                       int32_t layer,
                                                       NrtRGBAConfigHandle colourConfig);
    NrtResult Nrt_RenderingService_createTextRect(NrtRenderingServiceHandle renderingService,
                                                  NrtTextRectHandle* outputTextRect,
                                                  NrtTransform transform,
                                                  int32_t layer,
                                                  NrtRGBAConfigHandle colourConfig,
                                                  float fontSize,
                                                  const char* fontFilePath);
    NrtResult Nrt_RenderingService_getCamera(NrtRenderingServiceHandle renderingService, NrtCameraHandle* outputCamera);
    NrtResult Nrt_RenderingService_beginFrame(NrtRenderingServiceHandle renderingService);
    NrtResult Nrt_RenderingService_endFrame(NrtRenderingServiceHandle renderingService);
    NrtResult Nrt_RenderingService_setBackgroundColour(NrtRenderingServiceHandle renderingService, NrtRGBAConfigHandle colour);
    NrtResult Nrt_RenderingService_getTextureWithNothing(NrtRenderingServiceHandle renderingService,
                                                         NrtTextureHandle* outputTexture);
    NrtResult Nrt_RenderingService_getTextureWithFile(NrtRenderingServiceHandle renderingService,
                                                      NrtTextureHandle* outputTexture,
                                                      const char* fileTarget);
    NrtResult Nrt_RenderingService_getFontSet(NrtRenderingServiceHandle renderingService,
                                              NrtFontSetHandle* outputFontSet,
                                              const char* fileTarget,
                                              float fontSize);
    NrtResult Nrt_RenderingService_destroy(NrtRenderingServiceHandle renderingService);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H
