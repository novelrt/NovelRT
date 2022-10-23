// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtResult Nrt_TextureMetadata_Destroy(NrtTextureMetadataHandle textureMetadata)
    {
        if (textureMetadata == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<TextureMetadata*>(textureMetadata);

        return NRT_SUCCESS;
    }

    NrtUint8VectorHandle Nrt_TextureMetadata_GetData(NrtTextureMetadataHandle textureMetadata)
    {
        return reinterpret_cast<NrtUint8VectorHandle>(&reinterpret_cast<TextureMetadata*>(textureMetadata)->data);
    }

    uint32_t Nrt_TextureMetadata_GetWidth(NrtTextureMetadataHandle textureMetadata)
    {
        return reinterpret_cast<TextureMetadata*>(textureMetadata)->width;
    }

    uint32_t Nrt_TextureMetadata_GetHeight(NrtTextureMetadataHandle textureMetadata)
    {
        return reinterpret_cast<TextureMetadata*>(textureMetadata)->height;
    }

    size_t Nrt_TextureMetadata_GetPixelCount(NrtTextureMetadataHandle textureMetadata)
    {
        return reinterpret_cast<TextureMetadata*>(textureMetadata)->pixelCount;
    }

    NrtUuid Nrt_TextureMetadata_GetDatabaseHandle(NrtTextureMetadataHandle textureMetadata)
    {
        return *reinterpret_cast<NrtUuid*>(&reinterpret_cast<TextureMetadata*>(textureMetadata)->databaseHandle);
    }
}
