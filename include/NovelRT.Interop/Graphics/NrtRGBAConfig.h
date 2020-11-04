
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H
#define NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H

#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct RGBAConfigHandle* NrtRGBAConfig;

  NrtRGBAConfig Nrt_RGBAConfig_Create(int32_t r, int32_t g, int32_t b, int32_t a);
  NrtResult Nrt_RGBAConfig_getR(NrtRGBAConfig colourConfig, int32_t* outputValue);
  NrtResult Nrt_RGBAConfig_setR(NrtRGBAConfig colourConfig, int32_t inputValue);
  NrtResult Nrt_RGBAConfig_getG(NrtRGBAConfig colourConfig, int32_t* outputValue);
  NrtResult Nrt_RGBAConfig_setG(NrtRGBAConfig colourConfig, int32_t inputValue);
  NrtResult Nrt_RGBAConfig_getB(NrtRGBAConfig colourConfig, int32_t* outputValue);
  NrtResult Nrt_RGBAConfig_setB(NrtRGBAConfig colourConfig, int32_t inputValue);
  NrtResult Nrt_RGBAConfig_getA(NrtRGBAConfig colourConfig, int32_t* outputValue);
  NrtResult Nrt_RGBAConfig_setA(NrtRGBAConfig colourConfig, int32_t inputValue);

  NrtResult Nrt_RGBAConfig_getRScalar(NrtRGBAConfig colourConfig, float* outputValue);
  NrtResult Nrt_RGBAConfig_getGScalar(NrtRGBAConfig colourConfig, float* outputValue);
  NrtResult Nrt_RGBAConfig_getBScalar(NrtRGBAConfig colourConfig, float* outputValue);
  NrtResult Nrt_RGBAConfig_getAScalar(NrtRGBAConfig colourConfig, float* outputValue);
  NrtResult Nrt_RGBAConfig_destroy(NrtRGBAConfig);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H