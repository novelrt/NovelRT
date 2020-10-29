// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include "NovelRT.Interop/Audio/NovelRTAudioService.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Input/NovelRTKeyStateFrameChangeLog.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/DotNet/NovelRTRuntimeService.h"
#include "NovelRT.Interop/Utilities/NovelRTCommonEvents.h"
#include "NovelRT.Interop/Graphics/NovelRTRenderingService.h"
#include "NovelRT.Interop/NovelRTDebugService.h"

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#define NOVELRT_INTEROP_NOVELRUNNER_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct NovelRunnerHandle* NovelRTNovelRunner;

  NovelRTNovelRunner NovelRT_NovelRunner_create(int displayNumber);
  NovelRTNovelRunner NovelRT_NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate);
  int32_t NovelRT_NovelRunner_runNovel(NovelRTNovelRunner runner);
  int32_t NovelRT_NovelRunner_destroy(NovelRTNovelRunner runner);

  int32_t NovelRT_NovelRunner_getAudioService(NovelRTNovelRunner runner, NovelRTAudioService* outputService);
  int32_t NovelRT_NovelRunner_getInteractionService(NovelRTNovelRunner runner, NovelRTInteractionService* outputService);
  int32_t NovelRT_NovelRunner_getWindowingService(NovelRTNovelRunner runner, NovelRTWindowingService* outputService);
  int32_t NovelRT_NovelRunner_getRuntimeService(NovelRTNovelRunner runner, NovelRTRuntimeService* outputService);
  int32_t NovelRT_NovelRunner_getRenderer(NovelRTNovelRunner runner, NovelRTRenderingService* outputService);
  int32_t NovelRT_NovelRunner_getDebugService(NovelRTNovelRunner runner, NovelRTDebugService* outputService);

  int32_t NovelRT_NovelRunner_addUpdate(NovelRTNovelRunner runner, void(*func)(NovelRTTimestamp));
  int32_t NovelRT_NovelRunner_addSceneConstructionRequested(NovelRTNovelRunner runner, void(*func)());
  int32_t NovelRT_NovelRunner_getUpdateEvent(NovelRTNovelRunner runner, NovelRTUtilitiesEventWithTimestamp* outputEvent);
  int32_t NovelRT_NovelRunner_getSceneConstructionEvent(NovelRTNovelRunner runner, NovelRTUtilitiesEvent* outputEvent);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRUNNER_H
