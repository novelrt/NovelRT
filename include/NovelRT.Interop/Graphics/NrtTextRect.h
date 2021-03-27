
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_TextRect_getTransform(NrtTextRectHandle rect, NrtTransform* outputTransform);
    NrtResult Nrt_TextRect_setTransform(NrtTextRectHandle rect, NrtTransform inputTransform);
    int32_t Nrt_TextRect_getLayer(NrtTextRectHandle rect);
    NrtResult Nrt_TextRect_setLayer(NrtTextRectHandle rect, int32_t inputLayer);
    NrtBool Nrt_TextRect_getActive(NrtTextRectHandle rect);
    NrtResult Nrt_TextRect_setActive(NrtTextRectHandle rect, NrtBool inputBool);
    NrtResult Nrt_TextRect_executeObjectBehaviour(NrtTextRectHandle rect);
    NrtResult Nrt_TextRect_getColourConfig(NrtTextRectHandle rect, NrtRGBAConfigHandle* outputColourConfig);
    NrtResult Nrt_TextRect_setColourConfig(NrtTextRectHandle rect, NrtRGBAConfigHandle inputColourConfig);
    const char* Nrt_TextRect_getText(NrtTextRectHandle rect);
    NrtResult Nrt_TextRect_setText(NrtTextRectHandle rect, const char* inputText);
    NrtResult Nrt_TextRect_getFontSet(NrtTextRectHandle rect, NrtFontSetHandle* outputFontSet);
    NrtResult Nrt_TextRect_setFontSet(NrtTextRectHandle rect, NrtFontSetHandle inputFontSet);

    NrtResult Nrt_TextRect_getAsRenderObjectPtr(NrtTextRectHandle rect, NrtRenderObjectHandle* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
