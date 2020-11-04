// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "../Windowing/NrtWindowingService.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  NrtResult Nrt_RenderingService_create(NrtWindowingService windowingService, NrtRenderingService* outputRenderingService);
  NrtResult Nrt_RenderingService_initialiseRendering(NrtRenderingService renderingService); //this function has its own return codes, so in theory we can combine them both into the main return code
  NrtResult Nrt_RenderingService_tearDown(NrtRenderingService renderingService);
  NrtResult Nrt_RenderingService_createImageRectWithFile(NrtRenderingService renderingService, NrtImageRect* outputImageRect, NrtTransform transform, int32_t layer, const char* filePath, NrtRGBAConfig colourTint);
  NrtResult Nrt_RenderingService_createImageRectWithNothing(NrtRenderingService renderingService, NrtImageRect* outputImageRect, NrtTransform transform, int32_t layer, NrtRGBAConfig colourTint);
  NrtResult Nrt_RenderingService_createBasicFillRect(NrtRenderingService renderingService, NrtBasicFillRect* outputBasicFillRect, NrtTransform transform, int32_t layer, NrtRGBAConfig colourConfig);
  NrtResult Nrt_RenderingService_createTextRect(NrtRenderingService renderingService, NrtTextRect* outputTextRect, NrtTransform transform, int32_t layer, NrtRGBAConfig colourConfig, float fontSize, const char* fontFilePath);
  NrtResult Nrt_RenderingService_getCamera(NrtRenderingService renderingService, NrtCamera* outputCamera);
  NrtResult Nrt_RenderingService_beginFrame(NrtRenderingService renderingService);
  NrtResult Nrt_RenderingService_endFrame(NrtRenderingService renderingService);
  NrtResult Nrt_RenderingService_setBackgroundColour(NrtRenderingService renderingService, NrtRGBAConfig colour);
  NrtResult Nrt_RenderingService_getTextureWithNothing(NrtRenderingService renderingService, NrtTexture* outputTexture);
  NrtResult Nrt_RenderingService_getTextureWithFile(NrtRenderingService renderingService, NrtTexture* outputTexture, const char* fileTarget);
  NrtResult Nrt_RenderingService_getFontSet(NrtRenderingService renderingService, NrtFontSet* outputFontSet, const char* fileTarget, float fontSize, const char**errorMessage);
  NrtResult Nrt_RenderingService_destroy(NrtRenderingService renderingService);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H