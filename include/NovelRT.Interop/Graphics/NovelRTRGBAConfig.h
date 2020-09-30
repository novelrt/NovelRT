
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H
#define NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H

#include "../NovelRTInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct RGBAConfigHandle* NovelRTRGBAConfig;

  NovelRTRGBAConfig NovelRT_RGBAConfig_Create(int32_t r, int32_t g, int32_t b, int32_t a);
  int32_t NovelRT_RGBAConfig_getR(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_setR(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_getG(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_setG(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_getB(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_setB(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_getA(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_setA(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage);

  int32_t NovelRT_RGBAConfig_getRScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_getGScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_getBScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_getAScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage);
  int32_t NovelRT_RGBAConfig_destroy(NovelRTRGBAConfig, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H