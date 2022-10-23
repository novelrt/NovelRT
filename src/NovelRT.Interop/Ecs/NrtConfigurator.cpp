// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/Ecs/NrtConfigurator.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Utilities/Misc.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::PluginManagement;
using namespace NovelRT::Interop;

NrtConfiguratorHandle Nrt_Configurator_Create()
{
    return reinterpret_cast<NrtConfiguratorHandle>(new Configurator());
}

NrtResult Nrt_Configurator_AddDefaultSystemsAndComponents(NrtConfiguratorHandle configurator)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    unused(reinterpret_cast<Configurator*>(configurator)->WithDefaultSystemsAndComponents());

    return NRT_SUCCESS;
}
NrtResult Nrt_Configurator_Destroy(NrtConfiguratorHandle configurator)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    delete reinterpret_cast<Configurator*>(configurator);

    return NRT_SUCCESS;
}
NrtResult Nrt_Configurator_AddGraphicsPluginProvider(NrtConfiguratorHandle configurator,
                                                     NrtIGraphicsPluginProviderHandle provider)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (provider == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* pluginProvider = reinterpret_cast<IGraphicsPluginProvider*>(provider);
    auto providerSharedPtr = Lifetime::Find(pluginProvider);
    if (providerSharedPtr == nullptr) {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    unused(reinterpret_cast<Configurator*>(configurator)->WithPluginProvider<IGraphicsPluginProvider>(providerSharedPtr));

    return NRT_SUCCESS;
}
NrtResult Nrt_Configurator_AddWindowingPluginProvider(NrtConfiguratorHandle configurator,
                                                      NrtIWindowingPluginProviderHandle provider)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (provider == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* pluginProvider = reinterpret_cast<IWindowingPluginProvider*>(provider);
    auto providerSharedPtr = Lifetime::Find(pluginProvider);
    if (providerSharedPtr == nullptr) {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    unused(reinterpret_cast<Configurator*>(configurator)
        ->WithPluginProvider<IWindowingPluginProvider>(providerSharedPtr));

    return NRT_SUCCESS;
}
NrtResult Nrt_Configurator_AddResourceManagementPluginProvider(NrtConfiguratorHandle configurator,
                                                               NrtIResourceManagementPluginProviderHandle provider)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (provider == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* pluginProvider = reinterpret_cast<IResourceManagementPluginProvider*>(provider);
    auto providerSharedPtr = Lifetime::Find(pluginProvider);
    if (providerSharedPtr == nullptr) {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    unused(reinterpret_cast<Configurator*>(configurator)
        ->WithPluginProvider<IResourceManagementPluginProvider>(providerSharedPtr));

    return NRT_SUCCESS;
}
NrtResult Nrt_Configurator_AddInputPluginProvider(NrtConfiguratorHandle configurator,
                                                  NrtIInputPluginProviderHandle provider)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (provider == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* pluginProvider = reinterpret_cast<IInputPluginProvider*>(provider);
    auto providerSharedPtr = Lifetime::Find(pluginProvider);
    if (providerSharedPtr == nullptr) {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    unused(reinterpret_cast<Configurator*>(configurator)->WithPluginProvider<IInputPluginProvider>(providerSharedPtr));

    return NRT_SUCCESS;
}

NrtResult Nrt_Configurator_InitialiseAndRegisterComponents(NrtConfiguratorHandle configurator,
                                                           NrtSystemSchedulerHandle* outputSystemScheduler)
{
    if (configurator == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputSystemScheduler == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* configuratorPtr = reinterpret_cast<Configurator*>(configurator);
    // Move that scheduler to the heap.
    auto* systemScheduler = new SystemScheduler{configuratorPtr->InitialiseAndRegisterComponents()};
    *outputSystemScheduler = reinterpret_cast<NrtSystemSchedulerHandle>(systemScheduler);

    return NRT_SUCCESS;
}
