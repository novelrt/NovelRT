// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIRESOURCEMANAGEMENTPLUGINPROVIDER_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIRESOURCEMANAGEMENTPLUGINPROVIDER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IResourceManagementPluginProvider_Destroy(NrtIResourceManagementPluginProviderHandle plugin);

    NrtResult Nrt_IResourceManagementPluginProvider_GetResourceLoader(NrtIResourceManagementPluginProviderHandle plugin,
                                                                      NrtResourceLoaderHandle* outputLoader);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIRESOURCEMANAGEMENTPLUGINPROVIDER_H
