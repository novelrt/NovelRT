// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceLoader.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;
using namespace NovelRT::Interop;

NrtResult Nrt_ResourceLoader_GetResourcePath(NrtResourceLoaderHandle loader, char** outputPath)
{
    if (loader == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputPath == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto& path = reinterpret_cast<ResourceLoader*>(loader)->ResourcesRootDirectory();
    auto pathString = path.string();

#ifdef WIN32
    size_t length = pathString.length() + 1;
    *outputPath = static_cast<char*>(malloc(length));
    strcpy_s(*outputPath, length, pathString.c_str());
#else
    *outputPath = strdup(pathString.c_str());
#endif

    return NRT_SUCCESS;
}

NrtResult Nrt_ResourceLoader_SetResourcePath(NrtResourceLoaderHandle loader, const char* newPath)
{
    if (loader == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (newPath == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    reinterpret_cast<ResourceLoader*>(loader)->ResourcesRootDirectory() = newPath;

    return NRT_SUCCESS;
}

NrtResult Nrt_ResourceLoader_Destroy(NrtResourceLoaderHandle loader)
{
    if (loader == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (Lifetime::Release(reinterpret_cast<ResourceLoader*>(loader)))
    {
        return NRT_SUCCESS;
    }
    else
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
}
