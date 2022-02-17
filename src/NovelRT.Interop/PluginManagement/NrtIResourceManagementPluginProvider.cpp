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
        NrtResourceLoaderPtrHandle* resourceLoader)
    {
        if (plugin == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (resourceLoader == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppPlugin = reinterpret_cast<IResourceManagementPluginProvider*>(plugin);
        auto CppResource = CppPlugin->GetResourceLoader();
        *resourceLoader = reinterpret_cast<NrtResourceLoaderPtrHandle>(CppResource.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif