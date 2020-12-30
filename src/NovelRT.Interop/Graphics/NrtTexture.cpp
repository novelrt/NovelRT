// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/Graphics/NrtTexture.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  NrtResult Nrt_Texture_loadPngAsTexture(NrtTexture targetTexture, const char* file) {
    if (targetTexture == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);

    try
    {
      texturePtr->loadPngAsTexture(std::string(file));
    }
    catch (const Exceptions::InvalidOperationException)
    { // todo: handle error message
      return NRT_FAILURE_INVALID_OPERATION;
    }

    return NRT_SUCCESS;
  }

  const char* Nrt_Texture_getTextureFile(NrtTexture targetTexture) {
    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    return texturePtr->getTextureFile().c_str();
  }

  NrtGeoVector2F Nrt_Texture_getSize(NrtTexture targetTexture) {
    Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
    auto vec = texturePtr->getSize();
    return *reinterpret_cast<NrtGeoVector2F*>(&vec);
  }

#ifdef __cplusplus
}
#endif
