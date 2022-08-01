// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIGRAPHICSPLUGINPROVIDER_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIGRAPHICSPLUGINPROVIDER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IGraphicsPluginProvider_Destroy(NrtIGraphicsPluginProviderHandle plugin);

    NrtResult Nrt_IGraphicsPluginProvider_GetGraphicsProvider(NrtIGraphicsPluginProviderHandle plugin,
                                                              NrtGraphicsProviderHandle* outputProvider);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_NRTIGRAPHICSPLUGINPROVIDER_H
