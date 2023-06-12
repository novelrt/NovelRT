// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_RESOURCELOADER_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_RESOURCELOADER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    char* Nrt_ResourceLoader_GetResourcesRootDirectory(NrtResourceLoaderHandle resourceLoader);

    NrtResult Nrt_ResourceLoader_SetResourcesLoaderRootDirectory(NrtResourceLoaderHandle resourceLoader,
                                                                 const char* newDirectory);

    NrtBool Nrt_ResourceLoader_GetIsAssetDBInitialised(NrtResourceLoaderHandle resourceLoader);

    NrtResult Nrt_ResourceLoader_InitAssetDatabase(NrtResourceLoaderHandle resourceLoader);

    NrtUuidFilePathMapHandle Nrt_ResourceLoader_GetGuidsToFilePathsMap(NrtResourceLoaderHandle resourceLoader);

    NrtFilePathUuidMapHandle Nrt_ResourceLoader_GetFilePathsToGuidsMap(NrtResourceLoaderHandle resourceLoader);

    NrtResult Nrt_ResourceLoader_LoadTexture(NrtResourceLoaderHandle resourceLoader,
                                             const char* filePath,
                                             NrtTextureMetadataHandle* outTextureMetadata);

    NrtResult Nrt_ResourceLoader_LoadShaderSource(NrtResourceLoaderHandle resourceLoader,
                                                  const char* filePath,
                                                  NrtShaderMetadataHandle* outShaderMetadata);

    NrtResult Nrt_ResourceLoader_LoadPackage(NrtResourceLoaderHandle resourceLoader,
                                             const char* filePath,
                                             NrtBinaryPackageHandle* outBinaryPackage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_RESOURCELOADER_H
