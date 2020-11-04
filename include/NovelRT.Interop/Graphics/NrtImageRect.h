// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H
#define NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t Nrt_ImageRect_getTransform(NrtImageRect rect, NrtTransform* outputTransform);
  int32_t Nrt_ImageRect_setTransform(NrtImageRect rect, NrtTransform inputTransform);
  int32_t Nrt_ImageRect_getLayer(NrtImageRect rect, int32_t* outputLayer);
  int32_t Nrt_ImageRect_setLayer(NrtImageRect rect, int32_t inputLayer);
  int32_t Nrt_ImageRect_getActive(NrtImageRect rect, int32_t* outputBool);
  int32_t Nrt_ImageRect_setActive(NrtImageRect rect, int32_t inputBool);
  int32_t Nrt_ImageRect_executeObjectBehaviour(NrtImageRect rect);
  int32_t Nrt_ImageRect_getTexture(NrtImageRect rect, NrtTexture* outputTexture);
  int32_t Nrt_ImageRect_setTexture(NrtImageRect rect, NrtTexture inputTexture);
  int32_t Nrt_ImageRect_getColourTint(NrtImageRect rect, NrtRGBAConfig* outputColourTint);
  int32_t Nrt_ImageRect_setColourTint(NrtImageRect rect, NrtRGBAConfig inputColourTint);


  int32_t Nrt_ImageRect_getAsRenderObjectPtr(NrtImageRect rect, NrtRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H