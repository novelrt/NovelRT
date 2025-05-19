// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIWINDOWINGPLUGINPROVIDER_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIWINDOWINGPLUGINPROVIDER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IWindowingPluginProvider_Destroy(NrtIWindowingPluginProviderHandle plugin);

    NrtResult Nrt_IWindowingPluginProvider_GetWindowingDevice(NrtIWindowingPluginProviderHandle plugin,
                                                              NrtIWindowingDeviceHandle* outputDevice);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIWINDOWINGPLUGINPROVIDER_H
