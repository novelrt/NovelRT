// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/PluginManagement/NrtIGraphicsPluginProvider.h>
#include <NovelRT/PluginManagement/PluginManagement.h>

using namespace NovelRT::PluginManagement;
using namespace NovelRT::Interop;

NrtResult Nrt_IGraphicsPluginProvider_Destroy(NrtIGraphicsPluginProviderHandle plugin)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (!Lifetime::Release(reinterpret_cast<IGraphicsPluginProvider*>(plugin)))
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
    
    return NRT_SUCCESS;
}

NrtResult Nrt_IGraphicsPluginProvider_GetGraphicsProvider(NrtIGraphicsPluginProviderHandle plugin,
                                                          NrtGraphicsProviderHandle* outputProvider)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputProvider == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& graphicsProvider = reinterpret_cast<IGraphicsPluginProvider*>(plugin)->GetGraphicsProvider();
    *outputProvider = reinterpret_cast<NrtGraphicsProviderHandle>(graphicsProvider.get());

    Lifetime::KeepAlive(std::move(graphicsProvider));

    return NRT_SUCCESS;
}
