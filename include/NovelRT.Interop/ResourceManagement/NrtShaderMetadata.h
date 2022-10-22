// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_SHADERMETADATA_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_SHADERMETADATA_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_ShaderMetadata_Destroy(NrtShaderMetadataHandle shaderMetadata);

    NrtUint8VectorHandle Nrt_ShaderMetadata_GetShaderCode(NrtShaderMetadataHandle shaderMetadata);

    NrtUuid Nrt_ShaderMetadata_GetDatabaseHandle(NrtShaderMetadataHandle shaderMetadata);

#ifdef __cplusplus
};
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_SHADERMETADATA_H
