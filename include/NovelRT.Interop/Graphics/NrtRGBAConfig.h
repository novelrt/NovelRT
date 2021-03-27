
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H
#define NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRGBAConfigHandle Nrt_RGBAConfig_Create(int32_t r, int32_t g, int32_t b, int32_t a);
    int32_t Nrt_RGBAConfig_getR(NrtRGBAConfigHandle colourConfig);
    NrtResult Nrt_RGBAConfig_setR(NrtRGBAConfigHandle colourConfig, int32_t inputValue);
    int32_t Nrt_RGBAConfig_getG(NrtRGBAConfigHandle colourConfig);
    NrtResult Nrt_RGBAConfig_setG(NrtRGBAConfigHandle colourConfig, int32_t inputValue);
    int32_t Nrt_RGBAConfig_getB(NrtRGBAConfigHandle colourConfig);
    NrtResult Nrt_RGBAConfig_setB(NrtRGBAConfigHandle colourConfig, int32_t inputValue);
    int32_t Nrt_RGBAConfig_getA(NrtRGBAConfigHandle colourConfig);
    NrtResult Nrt_RGBAConfig_setA(NrtRGBAConfigHandle colourConfig, int32_t inputValue);

    float Nrt_RGBAConfig_getRScalar(NrtRGBAConfigHandle colourConfig);
    float Nrt_RGBAConfig_getGScalar(NrtRGBAConfigHandle colourConfig);
    float Nrt_RGBAConfig_getBScalar(NrtRGBAConfigHandle colourConfig);
    float Nrt_RGBAConfig_getAScalar(NrtRGBAConfigHandle colourConfig);
    NrtResult Nrt_RGBAConfig_destroy(NrtRGBAConfigHandle);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H
