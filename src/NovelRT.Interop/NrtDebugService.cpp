// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtDebugService.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#include <list>

std::list<std::shared_ptr<NovelRT::DebugService>> _debugCollection;
std::list<std::shared_ptr<NovelRT::Graphics::RenderingService>> _debugRendererCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtResult Nrt_DebugService_create(NrtUtilitiesEventHandle sceneConstructionEvent,
                                      NrtRenderingServiceHandle renderingService,
                                      NrtDebugServiceHandle* outputService)
    {
        if (sceneConstructionEvent == nullptr || renderingService == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Utilities::Event<> constructionEvent = *reinterpret_cast<Utilities::Event<>*>(sceneConstructionEvent);
        _debugRendererCollection.push_back(
            reinterpret_cast<Graphics::RenderingService*>(renderingService)->shared_from_this());

        DebugService* cppService = new DebugService(constructionEvent, _debugRendererCollection.back());
        *outputService = reinterpret_cast<NrtDebugServiceHandle>(cppService);
        return NRT_SUCCESS;
    }

    NrtBool Nrt_DebugService_getIsFpsCounterVisible(NrtDebugServiceHandle service)
    {
        DebugService* cppService = reinterpret_cast<DebugService*>(service);
        return static_cast<int32_t>(cppService->getIsFpsCounterVisible());
    }

    NrtResult Nrt_DebugService_setIsFpsCounterVisible(NrtDebugServiceHandle service, int32_t value)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        DebugService* cppService = reinterpret_cast<DebugService*>(service);
        cppService->setIsFpsCounterVisible(static_cast<bool>(value));
        return NRT_SUCCESS;
    }

    uint32_t Nrt_DebugService_getFramesPerSecond(NrtDebugServiceHandle service)
    {
        DebugService* cppService = reinterpret_cast<DebugService*>(service);
        return cppService->getFramesPerSecond();
    }

    NrtResult Nrt_DebugService_setFramesPerSecond(NrtDebugServiceHandle service, uint32_t value)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        DebugService* cppService = reinterpret_cast<DebugService*>(service);
        cppService->setFramesPerSecond(value);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
