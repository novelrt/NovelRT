// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/PluginManagement/NrtPluginManagement.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>


using namespace NovelRT;
using namespace PluginManagement;

std::list<std::shared_ptr<IWindowingPluginProvider>> _iWindowingPluginProviderCollection;
std::list<std::shared_ptr<IGraphicsPluginProvider>> _iGraphicsPluginProviderCollection;
std::list<std::shared_ptr<IInputPluginProvider>> _iInputPluginProviderCollection;
std::list<std::shared_ptr<IResourceManagementPluginProvider>> _iResourceManagementPluginProviderCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtDefaultPluginSelectorHandle Nrt_DefaultPluginSelector_Create()
    {
        auto selector = new DefaultPluginSelector();
        return reinterpret_cast<NrtDefaultPluginSelectorHandle>(selector);
    }

    NrtResult Nrt_DefaultPluginSelector_Destroy(NrtDefaultPluginSelectorHandle selector)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        delete cppSelector;
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IGraphicsPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIGraphicsPluginProviderPtrHandle* outputResult)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto graphicsPlugin = cppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>();
        _iGraphicsPluginProviderCollection.push_back(graphicsPlugin);
        *outputResult = reinterpret_cast<NrtIGraphicsPluginProviderPtrHandle>(
            _iGraphicsPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IGraphicsPluginProvider_Destroy(NrtIGraphicsPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto toDelete = reinterpret_cast<IGraphicsPluginProvider*>(provider)->shared_from_this();
        if (std::find(_iGraphicsPluginProviderCollection.begin(),
            _iGraphicsPluginProviderCollection.end(), toDelete) ==
            _iGraphicsPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _iGraphicsPluginProviderCollection.remove(toDelete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IWindowingPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIWindowingPluginProviderPtrHandle* outputResult)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto windowingPlugin = cppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
        _iWindowingPluginProviderCollection.push_back(windowingPlugin);
        *outputResult = reinterpret_cast<NrtIWindowingPluginProviderPtrHandle>(
            _iWindowingPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IWindowingPluginProvider_Destroy(NrtIWindowingPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto toDelete = reinterpret_cast<IWindowingPluginProvider*>(provider)->shared_from_this();
        if (std::find(_iWindowingPluginProviderCollection.begin(),
            _iWindowingPluginProviderCollection.end(), toDelete) ==
            _iWindowingPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _iWindowingPluginProviderCollection.remove(toDelete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IResourceManagementPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIResourceManagementPluginProviderPtrHandle* outputResult)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto resourceManagementPlugin = cppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>();
        _iResourceManagementPluginProviderCollection.push_back(resourceManagementPlugin);
        *outputResult = reinterpret_cast<NrtIResourceManagementPluginProviderPtrHandle>(
            _iResourceManagementPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IResourceManagementPluginProvider_Destroy(NrtIResourceManagementPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto toDelete = reinterpret_cast<IResourceManagementPluginProvider*>(provider)->shared_from_this();
        if (std::find(_iResourceManagementPluginProviderCollection.begin(),
            _iResourceManagementPluginProviderCollection.end(), toDelete) ==
            _iResourceManagementPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _iResourceManagementPluginProviderCollection.remove(toDelete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultPluginSelector_GetDefaultPluginType_IInputPluginProvider(
        NrtDefaultPluginSelectorHandle selector,
        NrtIInputPluginProviderPtrHandle* outputResult)
    {
        if (selector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSelector = reinterpret_cast<DefaultPluginSelector*>(selector);
        auto inputPlugin = cppSelector->GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
        _iInputPluginProviderCollection.push_back(inputPlugin);
        *outputResult = reinterpret_cast<NrtIInputPluginProviderPtrHandle>(
            _iInputPluginProviderCollection.back().get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_IInputPluginProvider_Destroy(NrtIInputPluginProviderPtrHandle provider)
    {
        if (provider == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto toDelete = reinterpret_cast<IInputPluginProvider*>(provider)->shared_from_this();
        if (std::find(_iInputPluginProviderCollection.begin(),
            _iInputPluginProviderCollection.end(), toDelete) ==
            _iInputPluginProviderCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _iInputPluginProviderCollection.remove(toDelete);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
