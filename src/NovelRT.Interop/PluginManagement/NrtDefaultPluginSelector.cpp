// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/PluginManagement/NrtDefaultPluginSelector.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include "../LifetimeExtender.h"

using namespace NovelRT::PluginManagement;
using namespace NovelRT::Interop;

NrtDefaultPluginSelectorHandle Nrt_DefaultPluginSelector_Create()
{
    auto pluginSelector = new DefaultPluginSelector();
    return reinterpret_cast<NrtDefaultPluginSelectorHandle>(pluginSelector);
}

NrtResult Nrt_DefaultPluginSelector_GetDefaultResourceManagementPluginForCurrentPlatform(
    NrtDefaultPluginSelectorHandle pluginSelector,
    NrtIResourceManagementPluginProviderHandle* outputResourceManagementPlugin)
{
    if (pluginSelector == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputResourceManagementPlugin == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& resourcePlugin = reinterpret_cast<DefaultPluginSelector*>(pluginSelector)
                                ->GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>();
    *outputResourceManagementPlugin =
        reinterpret_cast<NrtIResourceManagementPluginProviderHandle>(resourcePlugin.get());

    Lifetime::KeepAlive(resourcePlugin);

    return NRT_SUCCESS;
}
NrtResult Nrt_DefaultPluginSelector_GetDefaultGraphicsPluginForCurrentPlatform(
    NrtDefaultPluginSelectorHandle pluginSelector,
    NrtIGraphicsPluginProviderHandle* outputGraphicsPlugin)
{
    if (pluginSelector == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputGraphicsPlugin == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& graphicsPlugin = reinterpret_cast<DefaultPluginSelector*>(pluginSelector)
                                ->GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>();
    *outputGraphicsPlugin = reinterpret_cast<NrtIGraphicsPluginProviderHandle>(graphicsPlugin.get());

    Lifetime::KeepAlive(std::move(graphicsPlugin));

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultPluginSelector_GetDefaultInputPluginForCurrentPlatform(
    NrtDefaultPluginSelectorHandle pluginSelector,
    NrtIInputPluginProviderHandle* outputInputPlugin)
{
    if (pluginSelector == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputInputPlugin == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& inputPlugin = reinterpret_cast<DefaultPluginSelector*>(pluginSelector)
                             ->GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    *outputInputPlugin = reinterpret_cast<NrtIInputPluginProviderHandle>(inputPlugin.get());

    Lifetime::KeepAlive(std::move(inputPlugin));

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultPluginSelector_GetDefaultWindowingPluginForCurrentPlatform(
    NrtDefaultPluginSelectorHandle pluginSelector,
    NrtIWindowingPluginProviderHandle* outputWindowingPlugin)
{
    if (pluginSelector == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputWindowingPlugin == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto&& windowingPlugin = reinterpret_cast<DefaultPluginSelector*>(pluginSelector)
                                 ->GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    *outputWindowingPlugin = reinterpret_cast<NrtIWindowingPluginProviderHandle>(windowingPlugin.get());

    Lifetime::KeepAlive(std::move(windowingPlugin));

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultPluginSelector_Destroy(NrtDefaultPluginSelectorHandle pluginSelector)
{
    if (pluginSelector == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    delete reinterpret_cast<DefaultPluginSelector*>(pluginSelector);
    return NRT_SUCCESS;
}
