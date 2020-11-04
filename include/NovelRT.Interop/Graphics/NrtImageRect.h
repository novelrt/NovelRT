// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H
#define NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

  NrtResult Nrt_ImageRect_getTransform(NrtImageRect rect, NrtTransform* outputTransform);
  NrtResult Nrt_ImageRect_setTransform(NrtImageRect rect, NrtTransform inputTransform);
  NrtResult Nrt_ImageRect_getLayer(NrtImageRect rect, int32_t* outputLayer);
  NrtResult Nrt_ImageRect_setLayer(NrtImageRect rect, int32_t inputLayer);
  NrtResult Nrt_ImageRect_getActive(NrtImageRect rect, NrtBool* outputBool);
  NrtResult Nrt_ImageRect_setActive(NrtImageRect rect, NrtBool inputBool);
  NrtResult Nrt_ImageRect_executeObjectBehaviour(NrtImageRect rect);
  NrtResult Nrt_ImageRect_getTexture(NrtImageRect rect, NrtTexture* outputTexture);
  NrtResult Nrt_ImageRect_setTexture(NrtImageRect rect, NrtTexture inputTexture);
  NrtResult Nrt_ImageRect_getColourTint(NrtImageRect rect, NrtRGBAConfig* outputColourTint);
  NrtResult Nrt_ImageRect_setColourTint(NrtImageRect rect, NrtRGBAConfig inputColourTint);


  NrtResult Nrt_ImageRect_getAsRenderObjectPtr(NrtImageRect rect, NrtRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H