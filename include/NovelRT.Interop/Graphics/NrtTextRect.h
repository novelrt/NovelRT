
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H

#include "../NrtTransform.h"
#include "NrtGraphicsTypedefs.h"
#include "NrtRGBAConfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_TextRect_getTransform(NrtTextRect rect, NrtTransform* outputTransform);
    NrtResult Nrt_TextRect_setTransform(NrtTextRect rect, NrtTransform inputTransform);
    int32_t Nrt_TextRect_getLayer(NrtTextRect rect);
    NrtResult Nrt_TextRect_setLayer(NrtTextRect rect, int32_t inputLayer);
    NrtBool Nrt_TextRect_getActive(NrtTextRect rect);
    NrtResult Nrt_TextRect_setActive(NrtTextRect rect, NrtBool inputBool);
    NrtResult Nrt_TextRect_executeObjectBehaviour(NrtTextRect rect);
    NrtResult Nrt_TextRect_getColourConfig(NrtTextRect rect, NrtRGBAConfig* outputColourConfig);
    NrtResult Nrt_TextRect_setColourConfig(NrtTextRect rect, NrtRGBAConfig inputColourConfig);
    const char* Nrt_TextRect_getText(NrtTextRect rect);
    NrtResult Nrt_TextRect_setText(NrtTextRect rect, const char* inputText);
    NrtResult Nrt_TextRect_getFontSet(NrtTextRect rect, NrtFontSet* outputFontSet);
    NrtResult Nrt_TextRect_setFontSet(NrtTextRect rect, NrtFontSet inputFontSet);

    NrtResult Nrt_TextRect_getAsRenderObjectPtr(NrtTextRect rect, NrtRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //! NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
