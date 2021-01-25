// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include "Audio/NrtAudioService.h"
#include "DotNet/NrtRuntimeService.h"
#include "Graphics/NrtRenderingService.h"
#include "Input/NrtInteractionService.h"
#include "Input/NrtKeyStateFrameChangeLog.h"
#include "NrtDebugService.h"
#include "NrtInteropUtils.h"
#include "Timing/NrtTimestamp.h"
#include "Utilities/NrtCommonEvents.h"
#include <stdint.h>

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#define NOVELRT_INTEROP_NOVELRUNNER_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NovelRunnerHandle* NrtNovelRunner;

    NrtNovelRunner Nrt_NovelRunner_create(int32_t displayNumber);
    NrtNovelRunner Nrt_NovelRunner_createCustom(int32_t displayNumber,
                                                const char* windowTitle,
                                                uint32_t targetFrameRate);
    NrtResult Nrt_NovelRunner_runNovel(NrtNovelRunner runner);
    NrtResult Nrt_NovelRunner_destroy(NrtNovelRunner runner);

    NrtResult Nrt_NovelRunner_getAudioService(NrtNovelRunner runner, NrtAudioService* outputService);
    NrtResult Nrt_NovelRunner_getInteractionService(NrtNovelRunner runner, NrtInteractionService* outputService);
    NrtResult Nrt_NovelRunner_getWindowingService(NrtNovelRunner runner, NrtWindowingService* outputService);
    NrtResult Nrt_NovelRunner_getRuntimeService(NrtNovelRunner runner, NrtRuntimeService* outputService);
    NrtResult Nrt_NovelRunner_getRenderer(NrtNovelRunner runner, NrtRenderingService* outputService);
    NrtResult Nrt_NovelRunner_getDebugService(NrtNovelRunner runner, NrtDebugService* outputService);

    NrtResult Nrt_NovelRunner_addUpdate(NrtNovelRunner runner, void (*func)(NrtTimestamp));
    NrtResult Nrt_NovelRunner_addSceneConstructionRequested(NrtNovelRunner runner, void (*func)());
    NrtResult Nrt_NovelRunner_getUpdateEvent(NrtNovelRunner runner, NrtUtilitiesEventWithTimestamp* outputEvent);
    NrtResult Nrt_NovelRunner_getSceneConstructionEvent(NrtNovelRunner runner, NrtUtilitiesEvent* outputEvent);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRUNNER_H
