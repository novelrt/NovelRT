// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Graphics/NovelRTBasicFillRect.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

using namespace NovelRT;
using namespace NovelRT::Graphics;

//COSPLAY
#ifdef __cplusplus
extern "C" {
#endif

int32_t NovelRT_BasicFillRect_getTransform(NovelRTBasicFillRect rect, NovelRTTransform* outputTransform) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  *outputTransform = *reinterpret_cast<NovelRTTransform*>(&cppRect->transform());

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_setTransform(NovelRTBasicFillRect rect, NovelRTTransform inputTransform) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->transform() = *reinterpret_cast<Transform*>(&inputTransform);

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_getLayer(NovelRTBasicFillRect rect, int32_t* outputLayer) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  *outputLayer = cppRect->layer();

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_setLayer(NovelRTBasicFillRect rect, int32_t inputLayer) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->layer() = inputLayer;

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_getActive(NovelRTBasicFillRect rect, int32_t* outputBool) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  if(cppRect->getActive()) {
    *outputBool = NOVELRT_TRUE;
  }
  else {
    *outputBool = NOVELRT_FALSE;
  }

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_setActive(NovelRTBasicFillRect rect, int32_t inputBool) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);

  if(inputBool == NOVELRT_TRUE) {
    cppRect->setActive(true);
  }
  else {
    cppRect->setActive(false);
  }

  return NOVELRT_SUCCESS;
}


int32_t NovelRT_BasicFillRect_executeObjectBehaviour(NovelRTBasicFillRect rect) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->executeObjectBehaviour();

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_getColourConfig(NovelRTBasicFillRect rect, NovelRTRGBAConfig* outputColourConfig) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  auto colourConfig = cppRect->getColourConfig();
  *outputColourConfig = *reinterpret_cast<NovelRTRGBAConfig*>(&colourConfig);

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_setColourConfig(NovelRTBasicFillRect rect, NovelRTRGBAConfig inputColourConfig) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->setColourConfig(*reinterpret_cast<RGBAConfig*>(&inputColourConfig));

  return NOVELRT_SUCCESS;
}

int32_t NovelRT_BasicFillRect_getAsRenderObjectPtr(NovelRTBasicFillRect rect, NovelRTRenderObject* outputRenderObject) {
  if(rect == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  *outputRenderObject = reinterpret_cast<NovelRTRenderObject>(rect);

  return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif