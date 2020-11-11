// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Graphics/NrtRGBAConfig.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  NrtRGBAConfig Nrt_RGBAConfig_Create(int32_t r, int32_t g, int32_t b, int32_t a) {
   RGBAConfig* newColour = new RGBAConfig(r, g, b, a);

   return reinterpret_cast<NrtRGBAConfig>(newColour);
  }

  NrtResult Nrt_RGBAConfig_getR(NrtRGBAConfig colourConfig, int32_t* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getR();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_setR(NrtRGBAConfig colourConfig, int32_t inputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setR(inputValue);

    return NRT_SUCCESS;
  }
  
  NrtResult Nrt_RGBAConfig_getG(NrtRGBAConfig colourConfig, int32_t* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getG();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_setG(NrtRGBAConfig colourConfig, int32_t inputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setG(inputValue);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_getB(NrtRGBAConfig colourConfig, int32_t* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getB();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_setB(NrtRGBAConfig colourConfig, int32_t inputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setB(inputValue);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_getA(NrtRGBAConfig colourConfig, int32_t* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getA();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_setA(NrtRGBAConfig colourConfig, int32_t inputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setA(inputValue);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_getRScalar(NrtRGBAConfig colourConfig, float* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getRScalar();

    return NRT_SUCCESS;
  }
  
  NrtResult Nrt_RGBAConfig_getGScalar(NrtRGBAConfig colourConfig, float* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getGScalar();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_getBScalar(NrtRGBAConfig colourConfig, float* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getBScalar();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_getAScalar(NrtRGBAConfig colourConfig, float* outputValue) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getAScalar();

    return NRT_SUCCESS;
  }

  NrtResult Nrt_RGBAConfig_destroy(NrtRGBAConfig colourConfig) {
    if(colourConfig == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);

    delete colourConfigPtr;

    return NRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif