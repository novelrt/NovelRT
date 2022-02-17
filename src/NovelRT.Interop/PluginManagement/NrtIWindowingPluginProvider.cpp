// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/PluginManagement/NrtPluginManagement.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT;
using namespace PluginManagement;
using namespace Windowing;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IWindowingPluginProvider_GetWindowingDevice(
        NrtIWindowingPluginProviderPtrHandle plugin,
        NrtIWindowingDevicePtrHandle* windowingDevice)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (windowingDevice == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppPlugin = reinterpret_cast<IWindowingPluginProvider*>(plugin);
        auto CppWindowing = CppPlugin->GetWindowingDevice();
        *windowingDevice = reinterpret_cast<NrtIWindowingDevicePtrHandle>(CppWindowing.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif