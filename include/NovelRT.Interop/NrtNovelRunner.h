// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#define NOVELRT_INTEROP_NOVELRUNNER_H

#include "NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtNovelRunnerHandle Nrt_NovelRunner_create(int32_t displayNumber);
    NrtNovelRunnerHandle Nrt_NovelRunner_createCustom(int32_t displayNumber,
                                                const char* windowTitle,
                                                NrtWindowMode windowMode,
                                                uint32_t targetFrameRate);
    NrtResult Nrt_NovelRunner_runNovel(NrtNovelRunnerHandle runner);
    NrtResult Nrt_NovelRunner_destroy(NrtNovelRunnerHandle runner);

    NrtResult Nrt_NovelRunner_getAudioService(NrtNovelRunnerHandle runner, NrtAudioServiceHandle* outputService);
    NrtResult Nrt_NovelRunner_getInteractionService(NrtNovelRunnerHandle runner,
                                                    NrtInteractionServiceHandle* outputService);
    NrtResult Nrt_NovelRunner_getWindowingService(NrtNovelRunnerHandle runner,
                                                  NrtWindowingServiceHandle* outputService);
    NrtResult Nrt_NovelRunner_getRuntimeService(NrtNovelRunnerHandle runner, NrtRuntimeServiceHandle* outputService);
    NrtResult Nrt_NovelRunner_getRenderer(NrtNovelRunnerHandle runner, NrtRenderingServiceHandle* outputService);
    NrtResult Nrt_NovelRunner_getDebugService(NrtNovelRunnerHandle runner, NrtDebugServiceHandle* outputService);

    NrtResult Nrt_NovelRunner_addUpdate(NrtNovelRunnerHandle runner, void (*func)(NrtTimestamp));
    NrtResult Nrt_NovelRunner_addSceneConstructionRequested(NrtNovelRunnerHandle runner, void (*func)());
    NrtResult Nrt_NovelRunner_getUpdateEvent(NrtNovelRunnerHandle runner,
                                             NrtUtilitiesEventWithTimestampHandle* outputEvent);
    NrtResult Nrt_NovelRunner_getSceneConstructionEvent(NrtNovelRunnerHandle runner,
                                                        NrtUtilitiesEventHandle* outputEvent);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRUNNER_H
