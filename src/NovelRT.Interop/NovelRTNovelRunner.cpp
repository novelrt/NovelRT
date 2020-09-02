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

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  //TODO: FIX EVERYTHING SO WE CHECK SAFELY FOR NULLPTR, D'OH!

  NovelRTNovelRunner* NovelRunner_create(int displayNumber) {
    NovelRunner* runner = new NovelRunner(displayNumber);

    return reinterpret_cast<NovelRTNovelRunner*>(runner);
  }

  NovelRTNovelRunner* NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate) {
    NovelRunner* runner = new NovelRunner(displayNumber, windowTitle, targetFrameRate);

    return reinterpret_cast<NovelRTNovelRunner*>(runner);
  }

  int NovelRunner_runNovel(NovelRTNovelRunner* runner) {
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

    return cRunner->runNovel();
  }

  void NovelRunner_destroy(NovelRTNovelRunner* runner) {
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
    return cRunner->~NovelRunner();
  }

  NovelRTResult NovelRT_NovelRunner_getAudioService(NovelRTNovelRunner* runner, NovelRTAudioService* outputService, const char** errorMessage) {
    if (runner == nullptr || outputService == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
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

  NovelRTResult NovelRT_NovelRunner_getInteractionService(NovelRTNovelRunner* runner, NovelRTInteractionService* outputService, const char** errorMessage)  {
    if (runner == nullptr || outputService == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
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


  NovelRTResult NovelRT_NovelRunner_addUpdate(NovelRTNovelRunner* runner, void(*ptr)(NovelRTTimestamp), const char** errorMessage) {
    if (runner == nullptr || ptr == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

    //Disabled -W-unused-parameter here because I don't want delta being touched with every function ptr being added.
    cRunner->Update += [&](NovelRT::Timing::Timestamp delta){ ptr(reinterpret_cast<NovelRTTimestamp>(&delta)); };
    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_NovelRunner_addSceneConstructionRequested(NovelRTNovelRunner* runner, void(*ptr)(), const char** errorMessage) {
    if (runner == nullptr || ptr == nullptr) {
      if (errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

    //Disabled -W-unused-parameter here because I don't want delta being touched with every function ptr being added.
    cRunner->SceneConstructionRequested += [&](){ ptr(); };
    return NOVELRT_SUCCESS;
  }

  
#ifdef __cplusplus
}
#endif
