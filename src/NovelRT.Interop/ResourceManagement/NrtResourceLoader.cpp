// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT.Interop/ResourceManagement/NrtResourceLoader.h"
#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;
using namespace NovelRT::Exceptions;
using namespace NovelRT::Interop;

extern "C"
{
    char* Nrt_ResourceLoader_GetResourcesRootDirectory(NrtResourceLoaderHandle resourceLoader)
    {
        std::string cppPath = reinterpret_cast<ResourceLoader*>(resourceLoader)->ResourcesRootDirectory().string();

        size_t length = cppPath.length() + 1;
        char* returnPtr = static_cast<char*>(malloc(length));
        strcpy(returnPtr, cppPath.c_str());

        return returnPtr;
    }

    NrtResult Nrt_ResourceLoader_SetResourcesLoaderRootDirectory(NrtResourceLoaderHandle resourceLoader,
                                                                 const char* newDirectory)
    {
        if (resourceLoader == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (newDirectory == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::string newPath(newDirectory);
        std::filesystem::path cppPath;

        try
        {
            cppPath = newDirectory;
        }
        catch (const std::runtime_error&)
        {
            Nrt_SetErrMsgIsInvalidPathInternal();
            return NRT_FAILURE_INVALID_DIRECTORY_PATH;
        }

        // TODO: not sure if we want an additional error code for this.
        if (cppPath.is_relative())
        {
            Nrt_SetErrMsgIsInvalidPathInternal();
            return NRT_FAILURE_INVALID_DIRECTORY_PATH;
        }

        reinterpret_cast<ResourceLoader*>(resourceLoader)->ResourcesRootDirectory() = cppPath;

        return NRT_SUCCESS;
    }

    NrtBool Nrt_ResourceLoader_GetIsAssetDBInitialised(NrtResourceLoaderHandle resourceLoader)
    {
        return reinterpret_cast<ResourceLoader*>(resourceLoader)->GetIsAssetDBInitialised();
    }

    NrtResult Nrt_ResourceLoader_InitAssetDatabase(NrtResourceLoaderHandle resourceLoader)
    {
        if (resourceLoader == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        try
        {
            reinterpret_cast<ResourceLoader*>(resourceLoader)->InitAssetDatabase();
        }
        catch (const NovelRT::Exceptions::IOException&)
        {
            Nrt_SetErrMsgIsFileNotFoundInternal();
            return NRT_FAILURE_FILE_NOT_FOUND;
        }

        return NRT_SUCCESS;
    }

    NrtUuidFilePathMapHandle Nrt_ResourceLoader_GetGuidsToFilePathsMap(NrtResourceLoaderHandle resourceLoader)
    {
        return reinterpret_cast<NrtUuidFilePathMapHandle>(
            &reinterpret_cast<const ResourceLoader*>(resourceLoader)->GetGuidsToFilePathsMap());
    }

    NrtFilePathUuidMapHandle Nrt_ResourceLoader_GetFilePathsToGuidsMap(NrtResourceLoaderHandle resourceLoader)
    {
        return reinterpret_cast<NrtFilePathUuidMapHandle>(
            &reinterpret_cast<const ResourceLoader*>(resourceLoader)->GetFilePathsToGuidsMap());
    }

    NrtResult Nrt_ResourceLoader_LoadTexture(NrtResourceLoaderHandle resourceLoader,
                                             const char* filePath,
                                             NrtTextureMetadataHandle* outTextureMetadata)
    {
        if (resourceLoader == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outTextureMetadata == nullptr || filePath == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto returnPtr = new TextureMetadata();
        std::filesystem::path cppFilePath;

        try
        {
            cppFilePath = filePath;
        }
        catch (const std::runtime_error&)
        {
            Nrt_SetErrMsgIsInvalidPathInternal();
            return NRT_FAILURE_INVALID_DIRECTORY_PATH;
        }

        try
        {
            *returnPtr = reinterpret_cast<ResourceLoader*>(resourceLoader)->LoadTexture(cppFilePath);
        }
        catch (const FileNotFoundException&)
        {
            Nrt_SetErrMsgIsFileNotFoundInternal();
            return NRT_FAILURE_FILE_NOT_FOUND;
        }

        *outTextureMetadata = reinterpret_cast<NrtTextureMetadataHandle>(returnPtr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_ResourceLoader_LoadShaderSource(NrtResourceLoaderHandle resourceLoader,
                                                  const char* filePath,
                                                  NrtShaderMetadataHandle* outShaderMetadata)
    {
        if (resourceLoader == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outShaderMetadata == nullptr || filePath == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto returnPtr = new ShaderMetadata();
        std::filesystem::path cppFilePath;

        try
        {
            cppFilePath = filePath;
        }
        catch (const std::runtime_error&)
        {
            Nrt_SetErrMsgIsInvalidPathInternal();
            return NRT_FAILURE_INVALID_DIRECTORY_PATH;
        }

        try
        {
            *returnPtr = reinterpret_cast<ResourceLoader*>(resourceLoader)->LoadShaderSource(cppFilePath);
        }
        catch (const FileNotFoundException&)
        {
            Nrt_SetErrMsgIsFileNotFoundInternal();
            return NRT_FAILURE_FILE_NOT_FOUND;
        }

        *outShaderMetadata = reinterpret_cast<NrtShaderMetadataHandle>(returnPtr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_ResourceLoader_LoadPackage(NrtResourceLoaderHandle resourceLoader,
                                             const char* filePath,
                                             NrtBinaryPackageHandle* outBinaryPackage)
    {
        if (resourceLoader == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outBinaryPackage == nullptr || filePath == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto returnPtr = new BinaryPackage();
        std::filesystem::path cppFilePath;

        try
        {
            cppFilePath = filePath;
        }
        catch (const std::runtime_error&)
        {
            Nrt_SetErrMsgIsInvalidPathInternal();
            return NRT_FAILURE_INVALID_DIRECTORY_PATH;
        }

        try
        {
            *returnPtr = reinterpret_cast<ResourceLoader*>(resourceLoader)->LoadPackage(cppFilePath);
        }
        catch (const FileNotFoundException&)
        {
            Nrt_SetErrMsgIsFileNotFoundInternal();
            return NRT_FAILURE_FILE_NOT_FOUND;
        }

        *outBinaryPackage = reinterpret_cast<NrtBinaryPackageHandle>(returnPtr);

        return NRT_SUCCESS;
    }
}

NrtResult Nrt_ResourceLoader_Destroy(NrtResourceLoaderHandle resourceLoader)
{
    if (resourceLoader == nullptr)
    {
        Nrt_SetErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (Lifetime::Release(resourceLoader))
    {
        return NRT_SUCCESS;
    }
    else
    {
        Nrt_SetErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
}
