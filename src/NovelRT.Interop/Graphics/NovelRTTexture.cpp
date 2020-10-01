// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Graphics/NovelRTTexture.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_Texture_loadPngAsTexture(NovelRTTexture targetTexture, const char* file, const char** errorMessage) {
    if (targetTexture == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    texturePtr->loadPngAsTexture(std::string(file));

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Texture_getTextureFile(NovelRTTexture targetTexture, const char** outputFile, const char** errorMessage) {
    if (targetTexture == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    *outputFile = texturePtr->getTextureFile().c_str();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Texture_getSize(NovelRTTexture targetTexture, NovelRTGeoVector2F* outputSize, const char** errorMessage) {
    if (targetTexture == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    auto vec = texturePtr->getSize();
    *outputSize = *reinterpret_cast<NovelRTGeoVector2F*>(&vec);

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif