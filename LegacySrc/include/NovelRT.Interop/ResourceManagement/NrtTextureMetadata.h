// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_TEXTUREMETADATA_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_TEXTUREMETADATA_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_TextureMetadata_Destroy(NrtTextureMetadataHandle textureMetadata);

    NrtUint8VectorHandle Nrt_TextureMetadata_GetData(NrtTextureMetadataHandle textureMetadata);

    uint32_t Nrt_TextureMetadata_GetWidth(NrtTextureMetadataHandle textureMetadata);

    uint32_t Nrt_TextureMetadata_GetHeight(NrtTextureMetadataHandle textureMetadata);

    size_t Nrt_TextureMetadata_GetPixelCount(NrtTextureMetadataHandle textureMetadata);

    NrtUuid Nrt_TextureMetadata_GetDatabaseHandle(NrtTextureMetadataHandle textureMetadata);

#ifdef __cplusplus
};
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_TEXTUREMETADATA_H
