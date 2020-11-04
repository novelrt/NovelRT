// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Graphics/NrtTexture.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  int32_t Nrt_Texture_loadPngAsTexture(NrtTexture targetTexture, const char* file) {
    if (targetTexture == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    texturePtr->loadPngAsTexture(std::string(file));

    return NRT_SUCCESS;
  }

  int32_t Nrt_Texture_getTextureFile(NrtTexture targetTexture, const char** outputFile) {
    if (targetTexture == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    *outputFile = texturePtr->getTextureFile().c_str();

    return NRT_SUCCESS;
  }

  int32_t Nrt_Texture_getSize(NrtTexture targetTexture, NrtGeoVector2F* outputSize) {
    if (targetTexture == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    auto vec = texturePtr->getSize();
    *outputSize = *reinterpret_cast<NrtGeoVector2F*>(&vec);

    return NRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif