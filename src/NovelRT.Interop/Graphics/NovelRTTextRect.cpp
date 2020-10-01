
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Graphics/NovelRTTextRect.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif


  int32_t NovelRT_TextRect_getTransform(NovelRTTextRect rect, NovelRTTransform *outputTransform, const char **errorMessage) {
    if(rect == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    Transform cppTransform = textRectPtr->transform();
    *outputTransform = *reinterpret_cast<NovelRTTransform*>(&cppTransform);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_setTransform(NovelRTTextRect rect, NovelRTTransform inputTransform, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->transform() = *reinterpret_cast<Transform*>(&inputTransform);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_getLayer(NovelRTTextRect rect, int32_t *outputLayer, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    *outputLayer = textRectPtr->layer();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_setLayer(NovelRTTextRect rect, int32_t inputLayer, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->layer() = inputLayer;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_getActive(NovelRTTextRect rect, int32_t *outputBool, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

    if(textRectPtr->getActive()) {
      *outputBool = NOVELRT_TRUE;
    }
    else {
      *outputBool = NOVELRT_FALSE;
    }

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_setActive(NovelRTTextRect rect, int32_t inputBool, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

    if(inputBool == NOVELRT_TRUE) {
      textRectPtr->setActive(true);
    }
    else {
      textRectPtr->setActive(false);
    }

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_executeObjectBehaviour(NovelRTTextRect rect, const char **errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

    textRectPtr->executeObjectBehaviour();


    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_getColourConfig(NovelRTTextRect rect, NovelRTRGBAConfig* outputColourConfig, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    auto colourConfig = textRectPtr->getColourConfig();
    *outputColourConfig = reinterpret_cast<NovelRTRGBAConfig>(&outputColourConfig);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_setColourConfig(NovelRTTextRect rect, NovelRTRGBAConfig inputColourConfig, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->setColourConfig(*reinterpret_cast<RGBAConfig*>(inputColourConfig));

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_getText(NovelRTTextRect rect, const char** outputText, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    *outputText = textRectPtr->getText().c_str(); //TODO: This might break lol. Not sure.

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_setText(NovelRTTextRect rect, const char* inputText, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->setText(std::string(inputText));

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_getFontSet(NovelRTTextRect rect, NovelRTFontSet* outputFontSet, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    auto fontSet = textRectPtr->getFontSet();
    *outputFontSet = reinterpret_cast<NovelRTFontSet>(fontSet.get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_TextRect_setFontSet(NovelRTTextRect rect, NovelRTFontSet inputFontSet, const char** errorMessage) {
    if(rect == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
    textRectPtr->setFontSet(reinterpret_cast<FontSet*>(inputFontSet)->shared_from_this());

    return NOVELRT_SUCCESS;
  }


  int32_t NovelRT_TextRect_getAsRenderObjectPtr(NovelRTTextRect rect, NovelRTRenderObject* outputRenderObject, const char** errorMessage) {
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