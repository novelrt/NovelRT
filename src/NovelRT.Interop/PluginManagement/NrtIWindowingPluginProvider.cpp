// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/PluginManagement/NrtIWindowingPluginProvider.h>
#include <NovelRT/PluginManagement/PluginManagement.h>

using namespace NovelRT::PluginManagement;
using namespace NovelRT::Interop;

NrtResult Nrt_IWindowingPluginProvider_Destroy(NrtIWindowingPluginProviderHandle plugin)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (!Lifetime::Release(reinterpret_cast<IWindowingPluginProvider*>(plugin)))
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    return NRT_SUCCESS;
}
NrtResult Nrt_IWindowingPluginProvider_GetWindowingDevice(NrtIWindowingPluginProviderHandle plugin,
                                                          NrtIWindowingDeviceHandle* outputDevice)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputDevice == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& windowingDevice = reinterpret_cast<IWindowingPluginProvider*>(plugin)->GetWindowingDevice();
    *outputDevice = reinterpret_cast<NrtIWindowingDeviceHandle>(windowingDevice.get());
    Lifetime::KeepAlive(std::move(windowingDevice));

    return NRT_SUCCESS;
}
