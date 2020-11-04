// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_FONTSET_H
#define NOVELRT_INTEROP_GRAPHICS_FONTSET_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "NrtGraphicsTypedefs.h"
#include "../Maths/NrtGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  NrtResult Nrt_FontSet_loadFontAsTextureSet(NrtFontSet fontSet, const char* file, float fontSize);
  NrtResult Nrt_FontSet_getFontFile(NrtFontSet fontSet, const char** outputFontFile);
  NrtResult Nrt_FontSet_getFontSize(NrtFontSet fontSet, float* outputFontSize);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_FONTSET_H