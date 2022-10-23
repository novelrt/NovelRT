// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/PluginManagement/NrtIResourceManagementPluginProvider.h>
#include <NovelRT/PluginManagement/PluginManagement.h>

using namespace NovelRT::PluginManagement;
using namespace NovelRT::Interop;

NrtResult Nrt_IResourceManagementPluginProvider_Destroy(NrtIResourceManagementPluginProviderHandle plugin)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (!Lifetime::Release(reinterpret_cast<IResourceManagementPluginProvider*>(plugin)))
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
    
    return NRT_SUCCESS;
}

NrtResult Nrt_IResourceManagementPluginProvider_GetResourceLoader(NrtIResourceManagementPluginProviderHandle plugin,
                                                                  NrtResourceLoaderHandle* outputLoader)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputLoader == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& resourceLoader = reinterpret_cast<IResourceManagementPluginProvider*>(plugin)->GetResourceLoader();
    *outputLoader = reinterpret_cast<NrtResourceLoaderHandle>(resourceLoader.get());
    Lifetime::KeepAlive(std::move(resourceLoader));

    return NRT_SUCCESS;
}
