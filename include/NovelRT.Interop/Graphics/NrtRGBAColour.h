
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_RGBACOLOUR_H
#define NOVELRT_INTEROP_GRAPHICS_RGBACOLOUR_H

#include "../NrtTypedefs.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    float Nrt_RGBAColour_getRScalar(NrtRGBAColour colourConfig);
    float Nrt_RGBAColour_getGScalar(NrtRGBAColour colourConfig);
    float Nrt_RGBAColour_getBScalar(NrtRGBAColour colourConfig);
    float Nrt_RGBAColour_getAScalar(NrtRGBAColour colourConfig);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_RGBACOLOUR_H
