// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H
#define NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//base type
NrtResult Nrt_BasicFillRect_getTransform(NrtBasicFillRect rect, NrtTransform* outputTransform);
NrtResult Nrt_BasicFillRect_setTransform(NrtBasicFillRect rect, NrtTransform inputTransform);
NrtResult Nrt_BasicFillRect_getLayer(NrtBasicFillRect rect, int32_t* outputLayer);
NrtResult Nrt_BasicFillRect_setLayer(NrtBasicFillRect rect, int32_t inputLayer);
NrtResult Nrt_BasicFillRect_getActive(NrtBasicFillRect rect, NrtBool* outputBool);
NrtResult Nrt_BasicFillRect_setActive(NrtBasicFillRect rect, NrtBool inputBool);
NrtResult Nrt_BasicFillRect_executeObjectBehaviour(NrtBasicFillRect rect);

//actual type
NrtResult Nrt_BasicFillRect_getColourConfig(NrtBasicFillRect rect, NrtRGBAConfig* outputColourConfig);
NrtResult Nrt_BasicFillRect_setColourConfig(NrtBasicFillRect rect, NrtRGBAConfig inputColourConfig);

NrtResult Nrt_BasicFillRect_getAsRenderObjectPtr(NrtBasicFillRect rect, NrtRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H