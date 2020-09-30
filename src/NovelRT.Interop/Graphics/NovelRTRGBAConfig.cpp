// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Graphics/NovelRTRGBAConfig.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  NovelRTRGBAConfig NovelRT_RGBAConfig_Create(int32_t r, int32_t g, int32_t b, int32_t a) {
   RGBAConfig* newColour = new RGBAConfig(r, g, b, a);

   return reinterpret_cast<NovelRTRGBAConfig>(newColour);
  }

  int32_t NovelRT_RGBAConfig_getR(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getR();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_setR(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setR(inputValue);

    return NOVELRT_SUCCESS;
  }
  
  int32_t NovelRT_RGBAConfig_getG(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getG();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_setG(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setG(inputValue);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_getB(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getB();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_setB(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setB(inputValue);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_getA(NovelRTRGBAConfig colourConfig, int32_t* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getA();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_setA(NovelRTRGBAConfig colourConfig, int32_t inputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    colourConfigPtr->setA(inputValue);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_getRScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getRScalar();

    return NOVELRT_SUCCESS;
  }
  
  int32_t NovelRT_RGBAConfig_getGScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getGScalar();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_getBScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getBScalar();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_getAScalar(NovelRTRGBAConfig colourConfig, float* outputValue, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
    *outputValue = colourConfigPtr->getAScalar();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RGBAConfig_destroy(NovelRTRGBAConfig colourConfig, const char** errorMessage) {
    if(colourConfig == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);

    delete colourConfigPtr;

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif