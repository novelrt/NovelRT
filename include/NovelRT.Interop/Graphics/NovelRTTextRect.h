
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_TextRect_getTransform(NovelRTTextRect rect, NovelRTTransform* outputTransform);
  int32_t NovelRT_TextRect_setTransform(NovelRTTextRect rect, NovelRTTransform inputTransform);
  int32_t NovelRT_TextRect_getLayer(NovelRTTextRect rect, int32_t* outputLayer);
  int32_t NovelRT_TextRect_setLayer(NovelRTTextRect rect, int32_t inputLayer);
  int32_t NovelRT_TextRect_getActive(NovelRTTextRect rect, int32_t* outputBool);
  int32_t NovelRT_TextRect_setActive(NovelRTTextRect rect, int32_t inputBool);
  int32_t NovelRT_TextRect_executeObjectBehaviour(NovelRTTextRect rect);
  int32_t NovelRT_TextRect_getColourConfig(NovelRTTextRect rect, NovelRTRGBAConfig* outputColourConfig);
  int32_t NovelRT_TextRect_setColourConfig(NovelRTTextRect rect, NovelRTRGBAConfig inputColourConfig);
  int32_t NovelRT_TextRect_getText(NovelRTTextRect rect, const char** outputText);
  int32_t NovelRT_TextRect_setText(NovelRTTextRect rect, const char* inputText);
  int32_t NovelRT_TextRect_getFontSet(NovelRTTextRect rect, NovelRTFontSet* outputFontSet);
  int32_t NovelRT_TextRect_setFontSet(NovelRTTextRect rect, NovelRTFontSet inputFontSet);

  int32_t NovelRT_TextRect_getAsRenderObjectPtr(NovelRTTextRect rect, NovelRTRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_TEXTRECT_H