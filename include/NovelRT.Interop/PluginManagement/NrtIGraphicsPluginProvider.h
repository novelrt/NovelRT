// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_PLUGINMANAGEMENT_IGRAPHICSPLUGINPROVIDER_H
#define NOVELRT_INTEROP_PLUGINMANAGEMENT_IGRAPHICSPLUGINPROVIDER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IGraphicsPluginProvider_GetGraphicsProvider(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtGraphicsProviderPtrHandle* outputResult);

    NrtResult Nrt_IGraphicsPluginProvider_GetDefaultSelectedGraphicsAdapterForContext(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtGraphicsSurfaceContextPtrHandle context,
        NrtGraphicsAdapterPtrHandle* outputResult);

    NrtResult Nrt_IGraphicsPluginProvider_CreateSurfaceContext(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtIGraphicsSurfacePtrHandle windowingDevice,
        NrtGraphicsSurfaceContextPtrHandle* outputResult);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_PLUGINMANAGEMENT_IGRAPHICSPLUGINPROVIDER_H