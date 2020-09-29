// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "../Windowing/NovelRTWindowingService.h"
#include "NovelRTGraphicsTypedefs.h"

#ifndef NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H
#define NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_RenderingService_create(NovelRTWindowingService windowingService, NovelRTWindowingService* outputRenderingService, const char** errorMessage);
  int32_t NovelRT_RenderingService_initialiseRendering(NovelRTRenderingService renderingService, const char** errorMessage); //this function has its own return codes, so in theory we can combine them both into the main return code
  int32_t NovelRT_RenderingService_tearDown(NovelRTRenderingService renderingService, const char** errorMessage);
  int32_t NovelRT_RenderingService_createImageRectWithFile(NovelRTRenderingService renderingService, NovelRTImageRect* outputImageRect, NovelRTTransform transform, int32_t layer, const char* filePath, NovelRTRGBAConfig colourTint, const char** errorMessage);
  int32_t NovelRT_RenderingService_createImageRectWithNothing(NovelRTRenderingService renderingService, NovelRTImageRect* outputImageRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourTint, const char** errorMessage);
  int32_t NovelRT_RenderingService_createBasicFillRect(NovelRTRenderingService renderingService, NovelRTBasicFillRect* outputBasicFillRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourConfig, const char** errorMessage);
  int32_t NovelRT_RenderingService_createTextRect(NovelRTRenderingService renderingService, NovelRTTextRect* outputTextRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourConfig, float fontSize, const char* fontFilePath, const char** errorMessage);
  

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_RENDERINGSERVICE_H