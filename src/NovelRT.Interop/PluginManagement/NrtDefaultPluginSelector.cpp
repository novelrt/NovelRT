// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/PluginManagement/NrtPluginManagement.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>


using namespace NovelRT;
using namespace PluginManagement;

std::list<std::shared_ptr<IWindowingPluginProvider>> _IWindowingPluginProviderCollection;
std::list<std::shared_ptr<IGraphicsPluginProvider>> _IGraphicsPluginProviderCollection;
std::list<std::shared_ptr<IInputPluginProvider>> _IInputPluginProviderCollection;
std::list<std::shared_ptr<IResourceManagementPluginProvider>> _IResourceManagementPluginProviderCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtDefaultPluginSelectorHandle Nrt_DefaultPluginSelector_create()
    {
        auto Selector = new DefaultPluginSelector;
        return reinterpret_cast<NrtDefaultPluginSelectorHandle>(Selector);
    }

    NrtResult Nrt_DefaultPluginSelector_destroy(NrtDefaultPluginSelectorHandle selector)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto CppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        delete CppSelector;
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IGraphicsPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIGraphicsPluginProviderPtrHandle* output)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto IGraphics = CppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>();
        _IGraphicsPluginProviderCollection.push_back(IGraphics);
        *output = reinterpret_cast<NrtIGraphicsPluginProviderPtrHandle>(
            _IGraphicsPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IGraphicsPluginProvider_destroy(NrtIGraphicsPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto to_delete = reinterpret_cast<IGraphicsPluginProvider*>(provider)->shared_from_this();
        if (std::find(_IGraphicsPluginProviderCollection.begin(),
            _IGraphicsPluginProviderCollection.end(), to_delete) ==
            _IGraphicsPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _IGraphicsPluginProviderCollection.remove(to_delete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IWindowingPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIWindowingPluginProviderPtrHandle* output)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto IWindowing = CppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
        _IWindowingPluginProviderCollection.push_back(IWindowing);
        *output = reinterpret_cast<NrtIWindowingPluginProviderPtrHandle>(
            _IWindowingPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IWindowingPluginProvider_destroy(NrtIWindowingPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto to_delete = reinterpret_cast<IWindowingPluginProvider*>(provider)->shared_from_this();
        if (std::find(_IWindowingPluginProviderCollection.begin(),
            _IWindowingPluginProviderCollection.end(), to_delete) ==
            _IWindowingPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _IWindowingPluginProviderCollection.remove(to_delete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IResourceManagementPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIResourceManagementPluginProviderPtrHandle* output)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto IResource = CppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>();
        _IResourceManagementPluginProviderCollection.push_back(IResource);
        *output = reinterpret_cast<NrtIResourceManagementPluginProviderPtrHandle>(
            _IResourceManagementPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IResourceManagementPluginProvider_destroy(NrtIResourceManagementPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto to_delete = reinterpret_cast<IResourceManagementPluginProvider*>(provider)->shared_from_this();
        if (std::find(_IResourceManagementPluginProviderCollection.begin(),
            _IResourceManagementPluginProviderCollection.end(), to_delete) ==
            _IResourceManagementPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _IResourceManagementPluginProviderCollection.remove(to_delete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IInputPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIInputPluginProviderPtrHandle* output)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto IInput = CppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
        _IInputPluginProviderCollection.push_back(IInput);
        *output = reinterpret_cast<NrtIInputPluginProviderPtrHandle>(
            _IInputPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IInputPluginProvider_destroy(NrtIInputPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto to_delete = reinterpret_cast<IInputPluginProvider*>(provider)->shared_from_this();
        if (std::find(_IInputPluginProviderCollection.begin(),
            _IInputPluginProviderCollection.end(), to_delete) ==
            _IInputPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _IInputPluginProviderCollection.remove(to_delete);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif