// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include <list>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTTransform.h"
#include "NovelRT.Interop/Graphics/NovelRTImageRect.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_ImageRect_getTransform(NovelRTImageRect rect, NovelRTTransform *outputTransform, const char **errorMessage) {
    if(rect == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    Transform cppTransform = imageRectPtr->transform();
    *outputTransform = *reinterpret_cast<NovelRTTransform*>(&cppTransform);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_setTransform(NovelRTImageRect rect, NovelRTTransform inputTransform, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->transform() = *reinterpret_cast<Transform*>(&inputTransform);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_getLayer(NovelRTImageRect rect, int32_t *outputLayer, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    *outputLayer = imageRectPtr->layer();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_setLayer(NovelRTImageRect rect, int32_t inputLayer, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->layer() = inputLayer;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_getActive(NovelRTImageRect rect, int32_t *outputBool, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    if(imageRectPtr->getActive()) {
      *outputBool = NOVELRT_TRUE;
    }
    else {
      *outputBool = NOVELRT_FALSE;
    }

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_setActive(NovelRTImageRect rect, int32_t inputBool, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    if(inputBool == NOVELRT_TRUE) {
      imageRectPtr->setActive(true);
    }
    else {
      imageRectPtr->setActive(false);
    }

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_executeObjectBehaviour(NovelRTImageRect rect, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    imageRectPtr->executeObjectBehaviour();


    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_getTexture(NovelRTImageRect rect, NovelRTTexture *outputTexture, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);

    auto texture = imageRectPtr->texture();
    *outputTexture = reinterpret_cast<NovelRTTexture>(texture.get());
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_setTexture(NovelRTImageRect rect, NovelRTTexture inputTexture, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->texture() = reinterpret_cast<Texture*>(inputTexture)->shared_from_this();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_getColourTint(NovelRTImageRect rect, NovelRTRGBAConfig *outputColourTint, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    RGBAConfig colour = imageRectPtr->colourTint();
    *outputColourTint = *reinterpret_cast<NovelRTRGBAConfig*>(&colour);

    return NOVELRT_SUCCESS;

  }

  int32_t NovelRT_ImageRect_setColourTint(NovelRTImageRect rect, NovelRTRGBAConfig inputColourTint, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    imageRectPtr->colourTint() = *reinterpret_cast<RGBAConfig*>(inputColourTint);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_ImageRect_getAsRenderObjectPtr(NovelRTImageRect rect, NovelRTRenderObject* outputRenderObject, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    *outputRenderObject = reinterpret_cast<NovelRTRenderObject>(rect);

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif