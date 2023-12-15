// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_TEXTUREINFO_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_TEXTUREINFO_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_TextureInfo_Destroy(NrtTextureInfoHandle texture);

    char* Nrt_TextureInfo_GetTextureName(NrtTextureInfoHandle texture);

    uint32_t Nrt_TextureInfo_GetTextureWidth(NrtTextureInfoHandle texture);

    uint32_t Nrt_TextureInfo_GetTextureHeight(NrtTextureInfoHandle texture);

    NrtAtom Nrt_TextureInfo_GetEcsId(NrtTextureInfoHandle texture);

    NrtBool Nrt_TextureInfo_Equals(NrtTextureInfoHandle lhs, NrtTextureInfoHandle rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_TEXTUREINFO_H
