// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include <NovelRT.h>
#include <stdint.h>
#include <list>

std::list<std::shared_ptr<NovelRT::Audio::AudioService>> _audioCollection;
std::list<std::shared_ptr<NovelRT::Input::InteractionService>> _interactionCollection;
std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowingCollection;
std::list<std::shared_ptr<NovelRT::DotNet::RuntimeService>> _runtimeCollection;
std::list<std::shared_ptr<NovelRT::Graphics::RenderingService>> _rendererCollection;
std::list<std::shared_ptr<NovelRT::DebugService>> _debugServiceCollection;

#ifdef __cplusplus
extern "C" {
#endif

  NovelRTNovelRunner NovelRT_NovelRunner_create(int displayNumber) {
    NovelRT::NovelRunner* runner = new NovelRT::NovelRunner(displayNumber);
    return reinterpret_cast<NovelRTNovelRunner>(runner);
  }

  NovelRTNovelRunner NovelRT_NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate) {
    NovelRT::NovelRunner* runner = new NovelRT::NovelRunner(displayNumber, windowTitle, targetFrameRate);
    return reinterpret_cast<NovelRTNovelRunner>(runner);
  }

  int32_t NovelRT_NovelRunner_runNovel(NovelRTNovelRunner runner) {
    if (runner == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    cRunner->runNovel();
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_destroy(NovelRTNovelRunner runner) {
    if (runner == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }
    
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    
    cRunner->~NovelRunner();
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getAudioService(NovelRTNovelRunner runner, NovelRTAudioService* outputService) {
    if (runner == nullptr || outputService == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _audioCollection.push_back(cRunner->getAudioService());

    auto ptr = _audioCollection.back().get();
    if (ptr == nullptr) {
      return NOVELRT_FAILURE;
    }

    *outputService = reinterpret_cast<NovelRTAudioService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getInteractionService(NovelRTNovelRunner runner, NovelRTInteractionService* outputService)  {
    if (runner == nullptr || outputService == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }
    
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _interactionCollection.push_back(cRunner->getInteractionService());

    auto ptr = _interactionCollection.back().get();
    if (ptr == nullptr)
    {
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTInteractionService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getWindowingService(NovelRTNovelRunner runner, NovelRTWindowingService* outputService) {
    if (runner == nullptr || outputService == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }
    
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _windowingCollection.push_back(cRunner->getWindowingService());

    auto ptr = _windowingCollection.back().get();
    if (ptr == nullptr)
    {
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTWindowingService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getRuntimeService(NovelRTNovelRunner runner, NovelRTRuntimeService* outputService) {
    if (runner == nullptr || outputService == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _runtimeCollection.push_back(cRunner->getDotNetRuntimeService());

    auto ptr = _runtimeCollection.back().get();
    if (ptr == nullptr)
    {
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTRuntimeService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getRenderer(NovelRTNovelRunner runner, NovelRTRenderingService* outputService) {
    if (runner == nullptr || outputService == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _rendererCollection.push_back(cRunner->getRenderer());

    auto ptr = _rendererCollection.back().get();
    if (ptr == nullptr)
    {
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTRenderingService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getDebugService(NovelRTNovelRunner runner, NovelRTDebugService* outputService) {
    if (runner == nullptr || outputService == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }
    
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _debugServiceCollection.push_back(cRunner->getDebugService());

    auto ptr = _debugServiceCollection.back().get();
    if (ptr == nullptr)
    {
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTDebugService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_addUpdate(NovelRTNovelRunner runner, void(*func)(NovelRTTimestamp)) {
    if (runner == nullptr || func == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);

    cRunner->Update += [func](NovelRT::Timing::Timestamp delta){
      func(reinterpret_cast<NovelRTTimestamp>(&delta)); 
    };

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_addSceneConstructionRequested(NovelRTNovelRunner runner, void(*func)()) {
    if (runner == nullptr || func == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);

    cRunner->SceneConstructionRequested += [func](){ func(); };
    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_NovelRunner_getUpdateEvent(NovelRTNovelRunner runner, NovelRTUtilitiesEventWithTimestamp* outputEvent) {
    if (runner == nullptr || outputEvent == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    *outputEvent = reinterpret_cast<NovelRTUtilitiesEventWithTimestamp&>(cRunner->Update);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_NovelRunner_getSceneConstructionEvent(NovelRTNovelRunner runner, NovelRTUtilitiesEvent* outputEvent) {
    if (runner == nullptr || outputEvent == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    *outputEvent = reinterpret_cast<NovelRTUtilitiesEvent&>(cRunner->SceneConstructionRequested);
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
