// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Audio/NovelRTAudioService.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Windowing/NovelRTWindowingService.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include <NovelRT.h>
#include <stdint.h>
#include <list>

std::list<std::shared_ptr<NovelRT::Audio::AudioService>> _audioCollection;
std::list<std::shared_ptr<NovelRT::Input::InteractionService>> _interactionCollection;
std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowingCollection;

#ifdef __cplusplus
extern "C" {
#endif

  //TODO: FIX EVERYTHING SO WE CHECK SAFELY FOR NULLPTR, D'OH!

  NovelRTNovelRunner NovelRT_NovelRunner_create(int displayNumber) {
    NovelRT::NovelRunner* runner = new NovelRT::NovelRunner(displayNumber);
    return reinterpret_cast<NovelRTNovelRunner>(runner);
  }

  NovelRTNovelRunner NovelRT_NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate) {
    NovelRT::NovelRunner* runner = new NovelRT::NovelRunner(displayNumber, windowTitle, targetFrameRate);
    return reinterpret_cast<NovelRTNovelRunner>(runner);
  }

  NovelRTResult NovelRT_NovelRunner_runNovel(NovelRTNovelRunner runner, const char** errorMessage) {
    if (runner == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    cRunner->runNovel();
    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_NovelRunner_destroy(NovelRTNovelRunner runner, const char** errorMessage) {
    if (runner == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    
    cRunner->~NovelRunner();
    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_NovelRunner_getAudioService(NovelRTNovelRunner runner, NovelRTAudioService* outputService, const char** errorMessage) {
    if (runner == nullptr || outputService == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _audioCollection.push_back(cRunner->getAudioService());

    auto ptr = _audioCollection.back().get();
    if (ptr == nullptr)
    {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTAudioService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_NovelRunner_getInteractionService(NovelRTNovelRunner runner, NovelRTInteractionService* outputService, const char** errorMessage)  {
    if (runner == nullptr || outputService == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _interactionCollection.push_back(cRunner->getInteractionService());

    auto ptr = _interactionCollection.back().get();
    if (ptr == nullptr)
    {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTInteractionService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

NovelRTResult NovelRT_NovelRunner_getWindowingService(NovelRTNovelRunner runner, NovelRTWindowingService* outputService, const char** errorMessage) {
    if (runner == nullptr || outputService == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    _windowingCollection.push_back(cRunner->getWindowingService());

    auto ptr = _windowingCollection.back().get();
    if (ptr == nullptr)
    {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    *outputService = reinterpret_cast<NovelRTWindowingService>(ptr);
    
    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_NovelRunner_addUpdate(NovelRTNovelRunner runner, void(*func)(NovelRTTimestamp), const char** errorMessage) {
    if (runner == nullptr || func == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);

    cRunner->Update += [func](NovelRT::Timing::Timestamp delta){
       func(reinterpret_cast<NovelRTTimestamp>(&delta)); 
      };
    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_NovelRunner_addSceneConstructionRequested(NovelRTNovelRunner runner, void(*func)(), const char** errorMessage) {
    if (runner == nullptr || func == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);

    cRunner->SceneConstructionRequested += [func](){ func(); };
    return NOVELRT_SUCCESS;
  }

  
#ifdef __cplusplus
}
#endif
