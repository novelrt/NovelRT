// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include "NovelRT.Interop/Audio/NovelRTAudioService.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Input/NovelRTKeyStateFrameChangeLog.h"

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#define NOVELRT_INTEROP_NOVELRUNNER_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct NovelRunnerHandle* NovelRTNovelRunner;

  NovelRTNovelRunner* NovelRunner_create(int displayNumber);
  NovelRTNovelRunner* NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate);
  int NovelRunner_runNovel(NovelRTNovelRunner* runner);
  void NovelRunner_destroy(NovelRTNovelRunner* runner);

  
  NovelRTResult NovelRT_NovelRunner_getAudioService(NovelRTNovelRunner* runner, NovelRTAudioService* outputService, const char** errorMessage);
  NovelRTResult NovelRT_NovelRunner_getInteractionService(NovelRTNovelRunner* runner, NovelRTInteractionService* outputService, const char** errorMessage);
// /// Gets the Rendering Service associated with this Runner.
//     std::shared_ptr<Graphics::RenderingService> getRenderer() const;
//     /// Gets the Interaction Service associated with this Runner
//     std::shared_ptr<Input::InteractionService> getInteractionService() const;
//     /// Gets the Debug Service associated with this Runner.
//     std::shared_ptr<DebugService> getDebugService() const;
//     /// Gets the Audio Service associated with this Runner.
//     std::shared_ptr<Audio::AudioService> getAudioService() const;
//     /// Gets the .NET Runtime Service associated with this Runner.
//     std::shared_ptr<DotNet::RuntimeService> getDotNetRuntimeService() const;
//     /// Gets the Windowing Service associated with this Runner.
//     std::shared_ptr<Windowing::WindowingService> getWindowingService() const;  

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRUNNER_H
