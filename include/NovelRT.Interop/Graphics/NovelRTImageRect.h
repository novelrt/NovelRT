// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H
#define NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_ImageRect_getTransform(NovelRTImageRect rect, NovelRTTransform* outputTransform);
  int32_t NovelRT_ImageRect_setTransform(NovelRTImageRect rect, NovelRTTransform inputTransform);
  int32_t NovelRT_ImageRect_getLayer(NovelRTImageRect rect, int32_t* outputLayer);
  int32_t NovelRT_ImageRect_setLayer(NovelRTImageRect rect, int32_t inputLayer);
  int32_t NovelRT_ImageRect_getActive(NovelRTImageRect rect, int32_t* outputBool);
  int32_t NovelRT_ImageRect_setActive(NovelRTImageRect rect, int32_t inputBool);
  int32_t NovelRT_ImageRect_executeObjectBehaviour(NovelRTImageRect rect);
  int32_t NovelRT_ImageRect_getTexture(NovelRTImageRect rect, NovelRTTexture* outputTexture);
  int32_t NovelRT_ImageRect_setTexture(NovelRTImageRect rect, NovelRTTexture inputTexture);
  int32_t NovelRT_ImageRect_getColourTint(NovelRTImageRect rect, NovelRTRGBAConfig* outputColourTint);
  int32_t NovelRT_ImageRect_setColourTint(NovelRTImageRect rect, NovelRTRGBAConfig inputColourTint);


  int32_t NovelRT_ImageRect_getAsRenderObjectPtr(NovelRTImageRect rect, NovelRTRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H