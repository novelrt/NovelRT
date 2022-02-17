// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_IINPUTPLUGINPROVIDER_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_IINPUTPLUGINPROVIDER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IInputPluginProvider_GetInputService(
        NrtIInputPluginProviderPtrHandle plugin,
        NrtIInputDevicePtrHandle* inputService);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_IINPUTPLUGINPROVIDER_H