// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Graphics/NrtBasicFillRect.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.h"

using namespace NovelRT;
using namespace NovelRT::Graphics;

//COSPLAY
#ifdef __cplusplus
extern "C" {
#endif

int32_t Nrt_BasicFillRect_getTransform(NrtBasicFillRect rect, NrtTransform* outputTransform) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  *outputTransform = *reinterpret_cast<NrtTransform*>(&cppRect->transform());

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_setTransform(NrtBasicFillRect rect, NrtTransform inputTransform) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->transform() = *reinterpret_cast<Transform*>(&inputTransform);

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_getLayer(NrtBasicFillRect rect, int32_t* outputLayer) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  *outputLayer = cppRect->layer();

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_setLayer(NrtBasicFillRect rect, int32_t inputLayer) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }
  
  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->layer() = inputLayer;

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_getActive(NrtBasicFillRect rect, int32_t* outputBool) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  if(cppRect->getActive()) {
    *outputBool = NOVELRT_TRUE;
  }
  else {
    *outputBool = NOVELRT_FALSE;
  }

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_setActive(NrtBasicFillRect rect, int32_t inputBool) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);

  if(inputBool == NOVELRT_TRUE) {
    cppRect->setActive(true);
  }
  else {
    cppRect->setActive(false);
  }

  return NRT_SUCCESS;
}


int32_t Nrt_BasicFillRect_executeObjectBehaviour(NrtBasicFillRect rect) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->executeObjectBehaviour();

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_getColourConfig(NrtBasicFillRect rect, NrtRGBAConfig* outputColourConfig) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  auto colourConfig = cppRect->getColourConfig();
  *outputColourConfig = *reinterpret_cast<NrtRGBAConfig*>(&colourConfig);

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_setColourConfig(NrtBasicFillRect rect, NrtRGBAConfig inputColourConfig) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
  cppRect->setColourConfig(*reinterpret_cast<RGBAConfig*>(&inputColourConfig));

  return NRT_SUCCESS;
}

int32_t Nrt_BasicFillRect_getAsRenderObjectPtr(NrtBasicFillRect rect, NrtRenderObject* outputRenderObject) {
  if(rect == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  *outputRenderObject = reinterpret_cast<NrtRenderObject>(rect);

  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif