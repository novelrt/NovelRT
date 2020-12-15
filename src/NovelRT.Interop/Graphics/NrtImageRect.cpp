// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include <list>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/NrtTransform.h>
#include <NovelRT.Interop/Graphics/NrtImageRect.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  NrtTransform Nrt_ImageRect_getTransform(NrtImageRect rect) {
    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    Transform cppTransform = imageRectPtr->transform();
    return *reinterpret_cast<NrtTransform*>(&cppTransform);
  }

  NrtResult Nrt_ImageRect_setTransform(NrtImageRect rect, NrtTransform inputTransform) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->transform() = *reinterpret_cast<Transform*>(&inputTransform);

    return NRT_SUCCESS;
  }

  int32_t Nrt_ImageRect_getLayer(NrtImageRect rect) {
    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    return imageRectPtr->layer();
  }

  NrtResult Nrt_ImageRect_setLayer(NrtImageRect rect, int32_t inputLayer) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->layer() = inputLayer;

    return NRT_SUCCESS;
  }

  NrtBool Nrt_ImageRect_getActive(NrtImageRect rect) {
    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    if(imageRectPtr->getActive()) {
      return NRT_TRUE;
    }
    return NRT_FALSE;
  }

  NrtResult Nrt_ImageRect_setActive(NrtImageRect rect, NrtBool inputBool) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    if(inputBool == NRT_TRUE) {
      imageRectPtr->setActive(true);
    }
    else {
      imageRectPtr->setActive(false);
    }

    return NRT_SUCCESS;
  }

  NrtResult Nrt_ImageRect_executeObjectBehaviour(NrtImageRect rect) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    imageRectPtr->executeObjectBehaviour();


    return NRT_SUCCESS;
  }

  NrtResult Nrt_ImageRect_getTexture(NrtImageRect rect, NrtTexture *outputTexture) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    auto texture = imageRectPtr->texture();
    *outputTexture = reinterpret_cast<NrtTexture>(texture.get());

    return NRT_SUCCESS;
  }

  NrtResult Nrt_ImageRect_setTexture(NrtImageRect rect, NrtTexture inputTexture) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->texture() = reinterpret_cast<Texture*>(inputTexture)->shared_from_this();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_ImageRect_getColourTint(NrtImageRect rect, NrtRGBAConfig *outputColourTint) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    RGBAConfig colour = imageRectPtr->colourTint();
    *outputColourTint = *reinterpret_cast<NrtRGBAConfig*>(&colour);

    return NRT_SUCCESS;

  }

  NrtResult Nrt_ImageRect_setColourTint(NrtImageRect rect, NrtRGBAConfig inputColourTint) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->colourTint() = *reinterpret_cast<RGBAConfig*>(inputColourTint);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_ImageRect_getAsRenderObjectPtr(NrtImageRect rect, NrtRenderObject* outputRenderObject) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    *outputRenderObject = reinterpret_cast<NrtRenderObject>(rect);

    return NRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
