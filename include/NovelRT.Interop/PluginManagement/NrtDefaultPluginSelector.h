// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    NrtDefaultPluginSelectorHandle Nrt_DefaultPluginSelector_create();
    NrtResult Nrt_DefaultPluginSelector_destroy(NrtDefaultPluginSelectorHandle selector);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IGraphicsPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIGraphicsPluginProviderPtrHandle* output);
    NrtResult Nrt_IGraphicsPluginProvider_destroy(NrtIGraphicsPluginProviderPtrHandle provider);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IWindowingPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIWindowingPluginProviderPtrHandle* output);
    NrtResult Nrt_IWindowingPluginProvider_destroy(NrtIWindowingPluginProviderPtrHandle provider);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IResourceManagementPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIResourceManagementPluginProviderPtrHandle* output);
    NrtResult Nrt_IResourceManagementPluginProvider_destroy(
        NrtIResourceManagementPluginProviderPtrHandle provider);
    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IInputPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIInputPluginProviderPtrHandle* output);
    NrtResult Nrt_IInputPluginProvider_destroy(NrtIInputPluginProviderPtrHandle provider);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
