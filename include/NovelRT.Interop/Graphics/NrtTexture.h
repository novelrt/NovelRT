
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTURE_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTURE_H

#include "../NrtTransform.h"
#include "NrtRGBAConfig.h"
#include "NrtGraphicsTypedefs.h"
#include "../Maths/NrtGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  NrtResult Nrt_Texture_loadPngAsTexture(NrtTexture targetTexture, const char* file);
  const char* Nrt_Texture_getTextureFile(NrtTexture targetTexture);
  NrtGeoVector2F Nrt_Texture_getSize(NrtTexture targetTexture);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_TEXTURE_H
