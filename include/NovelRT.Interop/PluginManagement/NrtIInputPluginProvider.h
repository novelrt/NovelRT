// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIINPUTPLUGINPROVIDER_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIINPUTPLUGINPROVIDER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IInputPluginProvider_Destroy(NrtIInputPluginProviderHandle plugin);

    NrtResult Nrt_IInputPluginProvider_GetInputDevice(NrtIInputPluginProviderHandle plugin,
                                                      NrtIInputDeviceHandle* outputDevice);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIINPUTPLUGINPROVIDER_H
