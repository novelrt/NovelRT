
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H
#define NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRGBAColourHandle Nrt_RGBAColour_Create(int32_t r, int32_t g, int32_t b, int32_t a);
    int32_t Nrt_RGBAColour_getR(NrtRGBAColourHandle colourConfig);
    NrtResult Nrt_RGBAColour_setR(NrtRGBAColourHandle colourConfig, int32_t inputValue);
    int32_t Nrt_RGBAColour_getG(NrtRGBAColourHandle colourConfig);
    NrtResult Nrt_RGBAColour_setG(NrtRGBAColourHandle colourConfig, int32_t inputValue);
    int32_t Nrt_RGBAColour_getB(NrtRGBAColourHandle colourConfig);
    NrtResult Nrt_RGBAColour_setB(NrtRGBAColourHandle colourConfig, int32_t inputValue);
    int32_t Nrt_RGBAColour_getA(NrtRGBAColourHandle colourConfig);
    NrtResult Nrt_RGBAColour_setA(NrtRGBAColourHandle colourConfig, int32_t inputValue);

    float Nrt_RGBAColour_getRScalar(NrtRGBAColourHandle colourConfig);
    float Nrt_RGBAColour_getGScalar(NrtRGBAColourHandle colourConfig);
    float Nrt_RGBAColour_getBScalar(NrtRGBAColourHandle colourConfig);
    float Nrt_RGBAColour_getAScalar(NrtRGBAColourHandle colourConfig);
    NrtResult Nrt_RGBAColour_destroy(NrtRGBAColourHandle);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_RGBACONFIG_H
