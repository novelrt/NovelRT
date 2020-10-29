
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTURE_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTURE_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"
#include "../Maths/NovelRTGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_Texture_loadPngAsTexture(NovelRTTexture targetTexture, const char* file);
  int32_t NovelRT_Texture_getTextureFile(NovelRTTexture targetTexture, const char** outputFile);
  int32_t NovelRT_Texture_getSize(NovelRTTexture targetTexture, NovelRTGeoVector2F* outputSize);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_TEXTURE_H