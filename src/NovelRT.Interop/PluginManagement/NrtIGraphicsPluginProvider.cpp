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
        NrtGraphicsProviderPtrHandle* output)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppPlugin = reinterpret_cast<IGraphicsPluginProvider*>(plugin);
        auto GraphicsProvider = CppPlugin->GetGraphicsProvider();
        *output = reinterpret_cast<NrtGraphicsProviderPtrHandle>(GraphicsProvider.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IGraphicsPluginProvider_GetDefaultSelectedGraphicsAdapterForContext(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtGraphicsSurfaceContextPtrHandle context,
        NrtGraphicsAdapterPtrHandle* graphics_adapter)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (graphics_adapter == nullptr || context == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppPlugin = reinterpret_cast<IGraphicsPluginProvider*>(plugin);
        auto CppContext = reinterpret_cast<GraphicsSurfaceContext*>(context)->shared_from_this();
        auto GraphicsAdapter = CppPlugin->GetDefaultSelectedGraphicsAdapterForContext(CppContext);
        *graphics_adapter = reinterpret_cast<NrtGraphicsAdapterPtrHandle>(GraphicsAdapter.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IGraphicsPluginProvider_CreateSurfaceContext(
        NrtIGraphicsPluginProviderPtrHandle plugin,
        NrtIGraphicsSurfacePtrHandle windowingDevice,
        NrtGraphicsSurfaceContextPtrHandle* surface_context)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (surface_context == nullptr || windowingDevice == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppPlugin = reinterpret_cast<IGraphicsPluginProvider*>(plugin);
        auto CppWindowingDevice = reinterpret_cast<IGraphicsSurface*>(windowingDevice)->shared_from_this();
        auto CppContext = CppPlugin->CreateSurfaceContext(CppWindowingDevice);
        *surface_context = reinterpret_cast<NrtGraphicsSurfaceContextPtrHandle>(CppContext.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif