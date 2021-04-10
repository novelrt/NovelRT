
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TEXTURE_H
#define NOVELRT_INTEROP_GRAPHICS_TEXTURE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_Texture_loadPngAsTexture(NrtTextureHandle targetTexture, const char* file);
    const char* Nrt_Texture_getTextureFile(NrtTextureHandle targetTexture);
    NrtGeoVector2F Nrt_Texture_getSize(NrtTextureHandle targetTexture);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_TEXTURE_H
