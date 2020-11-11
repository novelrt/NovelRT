// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stdint.h>
#include <list>
#include "NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Utilities/NrtCommonEvents.h"
#include "NovelRT.Interop/Graphics/NrtRenderingService.h"
#include "NovelRT.Interop/NrtDebugService.h"
#include <NovelRT.h>

std::list<std::shared_ptr<NovelRT::DebugService>> _debugCollection;
std::list<std::shared_ptr<NovelRT::Graphics::RenderingService>> _debugRendererCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtResult Nrt_DebugService_create(NrtUtilitiesEvent sceneConstructionEvent, NrtRenderingService renderingService, NrtDebugService* outputService) {
  if (sceneConstructionEvent == nullptr || renderingService == nullptr ||outputService == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
    
  Utilities::Event<> constructionEvent = *reinterpret_cast<Utilities::Event<>*>(sceneConstructionEvent);
  _debugRendererCollection.push_back(reinterpret_cast<Graphics::RenderingService*>(renderingService)->shared_from_this());

  DebugService* cppService = new DebugService(constructionEvent, _debugRendererCollection.back());
  *outputService = reinterpret_cast<NrtDebugService>(cppService);
  return NRT_SUCCESS;
}

NrtResult Nrt_DebugService_getIsFpsCounterVisible(NrtDebugService service, int32_t* result) {
  if (service == nullptr || result == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  DebugService* cppService = reinterpret_cast<DebugService*>(service);
  *result = static_cast<int32_t>(cppService->getIsFpsCounterVisible());
  return NRT_SUCCESS;
}

NrtResult Nrt_DebugService_setIsFpsCounterVisible(NrtDebugService service, int32_t value) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  DebugService* cppService = reinterpret_cast<DebugService*>(service);
  cppService->setIsFpsCounterVisible(static_cast<bool>(value));
  return NRT_SUCCESS;
}

NrtResult Nrt_DebugService_getFramesPerSecond(NrtDebugService service, uint32_t* outputValue) {
  if (service == nullptr || outputValue == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  DebugService* cppService = reinterpret_cast<DebugService*>(service);
  *outputValue = cppService->getFramesPerSecond();
  return NRT_SUCCESS;
}

NrtResult Nrt_DebugService_setFramesPerSecond(NrtDebugService service, uint32_t value) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  DebugService* cppService = reinterpret_cast<DebugService*>(service);
  cppService->setFramesPerSecond(value);
  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
