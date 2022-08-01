// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTDEFAULTPLUGINSELECTOR_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTDEFAULTPLUGINSELECTOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtDefaultPluginSelectorHandle Nrt_DefaultPluginSelector_Create();

    NrtResult Nrt_DefaultPluginSelector_GetDefaultResourceManagementPluginForCurrentPlatform(
        NrtDefaultPluginSelectorHandle pluginSelector,
        NrtIResourceManagementPluginProviderHandle* outputResourceManagementPlugin);

    NrtResult Nrt_DefaultPluginSelector_GetDefaultGraphicsPluginForCurrentPlatform(
        NrtDefaultPluginSelectorHandle pluginSelector,
        NrtIGraphicsPluginProviderHandle* outputGraphicsPlugin);

    NrtResult Nrt_DefaultPluginSelector_GetDefaultInputPluginForCurrentPlatform(
        NrtDefaultPluginSelectorHandle pluginSelector,
        NrtIInputPluginProviderHandle* outputInputPlugin);

    NrtResult Nrt_DefaultPluginSelector_GetDefaultWindowingPluginForCurrentPlatform(
        NrtDefaultPluginSelectorHandle pluginSelector,
        NrtIWindowingPluginProviderHandle* outputWindowingPlugin);

    NrtResult Nrt_DefaultPluginSelector_Destroy(NrtDefaultPluginSelectorHandle pluginSelector);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTDEFAULTPLUGINSELECTOR_H
