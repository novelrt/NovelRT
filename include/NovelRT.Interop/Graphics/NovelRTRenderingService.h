// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "../Windowing/NovelRTWindowingService.h"
#include "NovelRTGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_RenderingService_create(NovelRTWindowingService windowingService, NovelRTRenderingService* outputRenderingService);
  int32_t NovelRT_RenderingService_initialiseRendering(NovelRTRenderingService renderingService); //this function has its own return codes, so in theory we can combine them both into the main return code
  int32_t NovelRT_RenderingService_tearDown(NovelRTRenderingService renderingService);
  int32_t NovelRT_RenderingService_createImageRectWithFile(NovelRTRenderingService renderingService, NovelRTImageRect* outputImageRect, NovelRTTransform transform, int32_t layer, const char* filePath, NovelRTRGBAConfig colourTint);
  int32_t NovelRT_RenderingService_createImageRectWithNothing(NovelRTRenderingService renderingService, NovelRTImageRect* outputImageRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourTint);
  int32_t NovelRT_RenderingService_createBasicFillRect(NovelRTRenderingService renderingService, NovelRTBasicFillRect* outputBasicFillRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourConfig);
  int32_t NovelRT_RenderingService_createTextRect(NovelRTRenderingService renderingService, NovelRTTextRect* outputTextRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourConfig, float fontSize, const char* fontFilePath);
  int32_t NovelRT_RenderingService_getCamera(NovelRTRenderingService renderingService, NovelRTCamera* outputCamera);
  int32_t NovelRT_RenderingService_beginFrame(NovelRTRenderingService renderingService);
  int32_t NovelRT_RenderingService_endFrame(NovelRTRenderingService renderingService);
  int32_t NovelRT_RenderingService_setBackgroundColour(NovelRTRenderingService renderingService, NovelRTRGBAConfig colour);
  int32_t NovelRT_RenderingService_getTextureWithNothing(NovelRTRenderingService renderingService, NovelRTTexture* outputTexture);
  int32_t NovelRT_RenderingService_getTextureWithFile(NovelRTRenderingService renderingService, NovelRTTexture* outputTexture, const char* fileTarget);
  int32_t NovelRT_RenderingService_getFontSet(NovelRTRenderingService renderingService, NovelRTFontSet* outputFontSet, const char* fileTarget, float fontSize, const char**errorMessage);
  int32_t NovelRT_RenderingService_destroy(NovelRTRenderingService renderingService);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H