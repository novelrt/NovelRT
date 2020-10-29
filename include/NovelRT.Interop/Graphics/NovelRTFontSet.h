// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_FONTSET_H
#define NOVELRT_INTEROP_GRAPHICS_FONTSET_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"
#include "../Maths/NovelRTGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_FontSet_loadFontAsTextureSet(NovelRTFontSet fontSet, const char* file, float fontSize);
  int32_t NovelRT_FontSet_getFontFile(NovelRTFontSet fontSet, const char** outputFontFile);
  int32_t NovelRT_FontSet_getFontSize(NovelRTFontSet fontSet, float* outputFontSize);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_FONTSET_H