// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/PluginManagement/NrtIInputPluginProvider.h>
#include <NovelRT/PluginManagement/PluginManagement.h>

using namespace NovelRT::PluginManagement;
using namespace NovelRT::Interop;

NrtResult Nrt_IInputPluginProvider_Destroy(NrtIInputPluginProviderHandle plugin)
{
    if (plugin == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (!Lifetime::Release(reinterpret_cast<IInputPluginProvider*>(plugin)))
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    return NRT_SUCCESS;
}

NrtResult Nrt_IInputPluginProvider_GetInputDevice(NrtIInputPluginProviderHandle plugin,
                                                  NrtIInputDeviceHandle* outputDevice)
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

    auto&& inputDevice = reinterpret_cast<IInputPluginProvider*>(plugin)->GetInputService();
    *outputDevice = reinterpret_cast<NrtIInputDeviceHandle>(inputDevice.get());
    Lifetime::KeepAlive(std::move(inputDevice));

    return NRT_SUCCESS;
}
