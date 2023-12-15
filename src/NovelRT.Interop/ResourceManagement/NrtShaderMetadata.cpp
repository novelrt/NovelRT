// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{

    NrtResult Nrt_ShaderMetadata_Destroy(NrtShaderMetadataHandle shaderMetadata)
    {
        if (shaderMetadata == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<ShaderMetadata*>(shaderMetadata);

        return NRT_SUCCESS;
    }

    NrtUint8VectorHandle Nrt_ShaderMetadata_GetShaderCode(NrtShaderMetadataHandle shaderMetadata)
    {
        return reinterpret_cast<NrtUint8VectorHandle>(&reinterpret_cast<ShaderMetadata*>(shaderMetadata)->shaderCode);
    }

    NrtUuid Nrt_ShaderMetadata_GetDatabaseHandle(NrtShaderMetadataHandle shaderMetadata)
    {
        return *reinterpret_cast<NrtUuid*>(&reinterpret_cast<ShaderMetadata*>(shaderMetadata)->databaseHandle);
    }
}
