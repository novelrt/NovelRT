// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stdint.h>
#include <list>
#include "NovelRT.Interop/Utilities/NovelRTCommonEvents.h"
#include "NovelRT.Interop/Graphics/NovelRTRenderingService.h"
#include "NovelRT.Interop/NovelRTDebugService.h"
#include <NovelRT.h>

std::list<std::shared_ptr<NovelRT::DebugService>> _debugCollection;
std::list<std::shared_ptr<NovelRT::Graphics::RenderingService>> _debugRendererCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

int32_t NovelRT_DebugService_create(NovelRTUtilitiesEvent sceneConstructionEvent, NovelRTRenderingService renderingService, NovelRTDebugService* outputService) {
    if (sceneConstructionEvent == nullptr || renderingService == nullptr ||outputService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    Utilities::Event<> constructionEvent = *reinterpret_cast<Utilities::Event<>*>(sceneConstructionEvent);
    _debugRendererCollection.push_back(reinterpret_cast<Graphics::RenderingService*>(renderingService)->shared_from_this());

    DebugService* cppService = new DebugService(constructionEvent, _debugRendererCollection.back());
    *outputService = reinterpret_cast<NovelRTDebugService>(cppService);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_DebugService_getIsFpsCounterVisible(NovelRTDebugService service, int32_t* result) {
    if (service == nullptr || result == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    DebugService* cppService = reinterpret_cast<DebugService*>(service);
    *result = static_cast<int32_t>(cppService->getIsFpsCounterVisible());
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_DebugService_setIsFpsCounterVisible(NovelRTDebugService service, int32_t value) {
    if (service == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    DebugService* cppService = reinterpret_cast<DebugService*>(service);
    cppService->setIsFpsCounterVisible(static_cast<bool>(value));
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_DebugService_getFramesPerSecond(NovelRTDebugService service, uint32_t* outputValue) {
    if (service == nullptr || outputValue == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    DebugService* cppService = reinterpret_cast<DebugService*>(service);
    *outputValue = cppService->getFramesPerSecond();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_DebugService_setFramesPerSecond(NovelRTDebugService service, uint32_t value) {
    if (service == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    DebugService* cppService = reinterpret_cast<DebugService*>(service);
    cppService->setFramesPerSecond(value);
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
