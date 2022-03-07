// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/PluginManagement/NrtPluginManagement.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT;
using namespace PluginManagement;
using namespace Input;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IInputPluginProvider_GetInputService(
        NrtIInputPluginProviderPtrHandle plugin,
        NrtIInputDevicePtrHandle* outputResult)
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

        auto cppPlugin = reinterpret_cast<IInputPluginProvider*>(plugin);
        auto inputDevice = cppPlugin->GetInputService();
        *outputResult = reinterpret_cast<NrtIInputDevicePtrHandle>(inputDevice.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
