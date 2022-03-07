// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    NrtDefaultPluginSelectorHandle Nrt_DefaultPluginSelector_Create();
    NrtResult Nrt_DefaultPluginSelector_Destroy(NrtDefaultPluginSelectorHandle selector);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IGraphicsPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIGraphicsPluginProviderPtrHandle* outputResult);
    NrtResult Nrt_IGraphicsPluginProvider_Destroy(NrtIGraphicsPluginProviderPtrHandle provider);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IWindowingPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIWindowingPluginProviderPtrHandle* outputResult);
    NrtResult Nrt_IWindowingPluginProvider_Destroy(NrtIWindowingPluginProviderPtrHandle provider);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IResourceManagementPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIResourceManagementPluginProviderPtrHandle* outputResult);
    NrtResult Nrt_IResourceManagementPluginProvider_Destroy(
        NrtIResourceManagementPluginProviderPtrHandle provider);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IInputPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIInputPluginProviderPtrHandle* outputResult);
    NrtResult Nrt_IInputPluginProvider_Destroy(NrtIInputPluginProviderPtrHandle provider);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
