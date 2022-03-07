// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/PluginManagement/NrtPluginManagement.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT;
using namespace PluginManagement;
using namespace Graphics;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IGraphicsPluginProvider_GetGraphicsProvider(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtGraphicsProviderPtrHandle* outputResult)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppPlugin = reinterpret_cast<IGraphicsPluginProvider*>(plugin);
        auto graphicsProvider = cppPlugin->GetGraphicsProvider();
        *outputResult = reinterpret_cast<NrtGraphicsProviderPtrHandle>(graphicsProvider.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IGraphicsPluginProvider_GetDefaultSelectedGraphicsAdapterForContext(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtGraphicsSurfaceContextPtrHandle context,
        NrtGraphicsAdapterPtrHandle* outputResult)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr || context == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppPlugin = reinterpret_cast<IGraphicsPluginProvider*>(plugin);
        auto cppContext = reinterpret_cast<GraphicsSurfaceContext*>(context)->shared_from_this();
        auto graphicsAdapter = cppPlugin->GetDefaultSelectedGraphicsAdapterForContext(cppContext);
        *outputResult = reinterpret_cast<NrtGraphicsAdapterPtrHandle>(graphicsAdapter.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IGraphicsPluginProvider_CreateSurfaceContext(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtIGraphicsSurfacePtrHandle windowingDevice,
        NrtGraphicsSurfaceContextPtrHandle* outputResult)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr || windowingDevice == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppPlugin = reinterpret_cast<IGraphicsPluginProvider*>(plugin);
        auto cppWindowingDevice = reinterpret_cast<IGraphicsSurface*>(windowingDevice)->shared_from_this();
        auto cppContext = cppPlugin->CreateSurfaceContext(cppWindowingDevice);
        *outputResult = reinterpret_cast<NrtGraphicsSurfaceContextPtrHandle>(cppContext.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
