
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_TextRect_getTransform(NovelRTTextRect rect, NovelRTTransform* outputTransform, const char** errorMessage);
  int32_t NovelRT_TextRect_setTransform(NovelRTTextRect rect, NovelRTTransform inputTransform, const char** errorMessage);
  int32_t NovelRT_TextRect_getLayer(NovelRTTextRect rect, int32_t* outputLayer, const char** errorMessage);
  int32_t NovelRT_TextRect_setLayer(NovelRTTextRect rect, int32_t inputLayer, const char** errorMessage);
  int32_t NovelRT_TextRect_getActive(NovelRTTextRect rect, int32_t* outputBool, const char** errorMessage);
  int32_t NovelRT_TextRect_setActive(NovelRTTextRect rect, int32_t inputBool, const char** errorMessage);
  int32_t NovelRT_TextRect_executeObjectBehaviour(NovelRTTextRect rect, const char** errorMessage);
  int32_t NovelRT_TextRect_getColourConfig(NovelRTTextRect rect, NovelRTRGBAConfig* outputColourConfig, const char** errorMessage);
  int32_t NovelRT_TextRect_setColourConfig(NovelRTTextRect rect, NovelRTRGBAConfig inputColourConfig, const char** errorMessage);
  int32_t NovelRT_TextRect_getText(NovelRTTextRect rect, const char** outputText, const char** errorMessage);
  int32_t NovelRT_TextRect_setText(NovelRTTextRect rect, const char* inputText, const char** errorMessage);
  int32_t NovelRT_TextRect_getFontSet(NovelRTTextRect rect, NovelRTFontSet* outputFontSet, const char** errorMessage);
  int32_t NovelRT_TextRect_setFontSet(NovelRTTextRect rect, NovelRTFontSet inputFontSet, const char** errorMessage);

  int32_t NovelRT_TextRect_getAsRenderObjectPtr(NovelRTTextRect rect, NovelRTRenderObject* outputRenderObject, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H