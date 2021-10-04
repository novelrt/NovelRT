// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H
#define NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // base type
    NrtTransform Nrt_BasicFillRect_getTransform(NrtBasicFillRectHandle rect);
    NrtResult Nrt_BasicFillRect_setTransform(NrtBasicFillRectHandle rect, NrtTransform inputTransform);
    int32_t Nrt_BasicFillRect_getLayer(NrtBasicFillRectHandle rect);
    NrtResult Nrt_BasicFillRect_setLayer(NrtBasicFillRectHandle rect, int32_t inputLayer);
    NrtBool Nrt_BasicFillRect_getActive(NrtBasicFillRectHandle rect);
    NrtResult Nrt_BasicFillRect_setActive(NrtBasicFillRectHandle rect, NrtBool inputBool);
    NrtResult Nrt_BasicFillRect_executeObjectBehaviour(NrtBasicFillRectHandle rect);

    // actual type
    NrtResult Nrt_BasicFillRect_getColourConfig(NrtBasicFillRectHandle rect, NrtRGBAColourHandle* outputColourConfig);
    NrtResult Nrt_BasicFillRect_setColourConfig(NrtBasicFillRectHandle rect, NrtRGBAColourHandle inputColourConfig);

    NrtResult Nrt_BasicFillRect_getAsRenderObjectPtr(NrtBasicFillRectHandle rect,
                                                     NrtRenderObjectHandle* outputRenderObject);
    NrtResult Nrt_BasicFillRect_destroy(NrtBasicFillRectHandle rect);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H
