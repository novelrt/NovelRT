
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Graphics/NovelRTFontSet.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_FontSet_loadFontAsTextureSet(NovelRTFontSet fontSet, const char* file, float fontSize) {
    if(fontSet == nullptr) {      return NOVELRT_FAILURE;
    }

    FontSet* fontSetPtr = reinterpret_cast<FontSet*>(fontSet);
    fontSetPtr->loadFontAsTextureSet(std::string(file), fontSize);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_FontSet_getFontFile(NovelRTFontSet fontSet, const char** outputFontFile) {
    if(fontSet == nullptr) {      return NOVELRT_FAILURE;
    }

    FontSet* fontSetPtr = reinterpret_cast<FontSet*>(fontSet);
    *outputFontFile = fontSetPtr->getFontFile().c_str();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_FontSet_getFontSize(NovelRTFontSet fontSet, float* outputFontSize) {
    if(fontSet == nullptr) {      return NOVELRT_FAILURE;
    }

    FontSet* fontSetPtr = reinterpret_cast<FontSet*>(fontSet);
    *outputFontSize = fontSetPtr->getFontSize();

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif