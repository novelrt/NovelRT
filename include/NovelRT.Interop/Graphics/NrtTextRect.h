
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t Nrt_TextRect_getTransform(NrtTextRect rect, NrtTransform* outputTransform);
  int32_t Nrt_TextRect_setTransform(NrtTextRect rect, NrtTransform inputTransform);
  int32_t Nrt_TextRect_getLayer(NrtTextRect rect, int32_t* outputLayer);
  int32_t Nrt_TextRect_setLayer(NrtTextRect rect, int32_t inputLayer);
  int32_t Nrt_TextRect_getActive(NrtTextRect rect, int32_t* outputBool);
  int32_t Nrt_TextRect_setActive(NrtTextRect rect, int32_t inputBool);
  int32_t Nrt_TextRect_executeObjectBehaviour(NrtTextRect rect);
  int32_t Nrt_TextRect_getColourConfig(NrtTextRect rect, NrtRGBAConfig* outputColourConfig);
  int32_t Nrt_TextRect_setColourConfig(NrtTextRect rect, NrtRGBAConfig inputColourConfig);
  int32_t Nrt_TextRect_getText(NrtTextRect rect, const char** outputText);
  int32_t Nrt_TextRect_setText(NrtTextRect rect, const char* inputText);
  int32_t Nrt_TextRect_getFontSet(NrtTextRect rect, NrtFontSet* outputFontSet);
  int32_t Nrt_TextRect_setFontSet(NrtTextRect rect, NrtFontSet inputFontSet);

  int32_t Nrt_TextRect_getAsRenderObjectPtr(NrtTextRect rect, NrtRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H