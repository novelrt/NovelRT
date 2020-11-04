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

  int32_t Nrt_RenderingService_create(NrtWindowingService windowingService, NrtRenderingService* outputRenderingService);
  int32_t Nrt_RenderingService_initialiseRendering(NrtRenderingService renderingService); //this function has its own return codes, so in theory we can combine them both into the main return code
  int32_t Nrt_RenderingService_tearDown(NrtRenderingService renderingService);
  int32_t Nrt_RenderingService_createImageRectWithFile(NrtRenderingService renderingService, NrtImageRect* outputImageRect, NrtTransform transform, int32_t layer, const char* filePath, NrtRGBAConfig colourTint);
  int32_t Nrt_RenderingService_createImageRectWithNothing(NrtRenderingService renderingService, NrtImageRect* outputImageRect, NrtTransform transform, int32_t layer, NrtRGBAConfig colourTint);
  int32_t Nrt_RenderingService_createBasicFillRect(NrtRenderingService renderingService, NrtBasicFillRect* outputBasicFillRect, NrtTransform transform, int32_t layer, NrtRGBAConfig colourConfig);
  int32_t Nrt_RenderingService_createTextRect(NrtRenderingService renderingService, NrtTextRect* outputTextRect, NrtTransform transform, int32_t layer, NrtRGBAConfig colourConfig, float fontSize, const char* fontFilePath);
  int32_t Nrt_RenderingService_getCamera(NrtRenderingService renderingService, NrtCamera* outputCamera);
  int32_t Nrt_RenderingService_beginFrame(NrtRenderingService renderingService);
  int32_t Nrt_RenderingService_endFrame(NrtRenderingService renderingService);
  int32_t Nrt_RenderingService_setBackgroundColour(NrtRenderingService renderingService, NrtRGBAConfig colour);
  int32_t Nrt_RenderingService_getTextureWithNothing(NrtRenderingService renderingService, NrtTexture* outputTexture);
  int32_t Nrt_RenderingService_getTextureWithFile(NrtRenderingService renderingService, NrtTexture* outputTexture, const char* fileTarget);
  int32_t Nrt_RenderingService_getFontSet(NrtRenderingService renderingService, NrtFontSet* outputFontSet, const char* fileTarget, float fontSize, const char**errorMessage);
  int32_t Nrt_RenderingService_destroy(NrtRenderingService renderingService);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H