// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/PluginManagement/NrtPluginManagement.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT;
using namespace PluginManagement;
using namespace ResourceManagement;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IResourceManagementPluginProvider_GetResourceLoader(
        NrtIResourceManagementPluginProviderPtrHandle plugin,
        NrtResourceLoaderPtrHandle* outputResult)
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

        auto cppPlugin = reinterpret_cast<IResourceManagementPluginProvider*>(plugin);
        auto resourceLoader = cppPlugin->GetResourceLoader();
        *outputResult = reinterpret_cast<NrtResourceLoaderPtrHandle>(resourceLoader.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
