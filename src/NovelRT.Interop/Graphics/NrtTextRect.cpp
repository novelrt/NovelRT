// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Graphics/NrtTextRect.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif


  NrtResult Nrt_TextRect_getTransform(NrtTextRect rect, NrtTransform *outputTransform) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    Transform cppTransform = textRectPtr->transform();
    *outputTransform = *reinterpret_cast<NrtTransform*>(&cppTransform);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_TextRect_setTransform(NrtTextRect rect, NrtTransform inputTransform) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->transform() = *reinterpret_cast<Transform*>(&inputTransform);

    return NRT_SUCCESS;
  }

  int32_t Nrt_TextRect_getLayer(NrtTextRect rect) {
    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    return textRectPtr->layer();
  }

  NrtResult Nrt_TextRect_setLayer(NrtTextRect rect, int32_t inputLayer) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->layer() = inputLayer;

    return NRT_SUCCESS;
  }

  NrtBool Nrt_TextRect_getActive(NrtTextRect rect) {
    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

    if(textRectPtr->getActive()) {
      return NRT_TRUE;
    }
    return NRT_FALSE;
  }

  NrtResult Nrt_TextRect_setActive(NrtTextRect rect, NrtBool inputBool) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

    if(inputBool == NRT_TRUE) {
      textRectPtr->setActive(true);
    }
    else {
      textRectPtr->setActive(false);
    }

    return NRT_SUCCESS;
  }

  NrtResult Nrt_TextRect_executeObjectBehaviour(NrtTextRect rect) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

    textRectPtr->executeObjectBehaviour();


    return NRT_SUCCESS;
  }

  NrtResult Nrt_TextRect_getColourConfig(NrtTextRect rect, NrtRGBAConfig* outputColourConfig) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    auto colourConfig = textRectPtr->getColourConfig();
    *outputColourConfig = reinterpret_cast<NrtRGBAConfig>(&colourConfig);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_TextRect_setColourConfig(NrtTextRect rect, NrtRGBAConfig inputColourConfig) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->setColourConfig(*reinterpret_cast<RGBAConfig*>(inputColourConfig));

    return NRT_SUCCESS;
  }

  const char* Nrt_TextRect_getText(NrtTextRect rect) {
    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    std::string* text = new std::string(textRectPtr->getText());
    return text->c_str();
  }

  NrtResult Nrt_TextRect_setText(NrtTextRect rect, const char* inputText) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->setText(std::string(inputText));

    return NRT_SUCCESS;
  }

  NrtResult Nrt_TextRect_getFontSet(NrtTextRect rect, NrtFontSet* outputFontSet) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    auto fontSet = textRectPtr->getFontSet();
    *outputFontSet = reinterpret_cast<NrtFontSet>(fontSet.get());

    return NRT_SUCCESS;
  }

  NrtResult Nrt_TextRect_setFontSet(NrtTextRect rect, NrtFontSet inputFontSet) {
    if(rect == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->setFontSet(reinterpret_cast<FontSet*>(inputFontSet)->shared_from_this());

    return NRT_SUCCESS;
  }


  NrtResult Nrt_TextRect_getAsRenderObjectPtr(NrtTextRect rect, NrtRenderObject* outputRenderObject) {
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
