// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_TIMING_STEPTIMER_H
#define NOVELRT_INTEROP_TIMING_STEPTIMER_H

#include "../NrtInteropUtils.h"
#include "NrtTimestamp.h"
#include "../Utilities/NrtCommonEvents.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StepTimerHandle* NrtStepTimer;

NrtResult Nrt_StepTimer_create(uint32_t targetFrameRate, double maxSecondDelta, NrtStepTimer* output);
NrtResult Nrt_StepTimer_getElapsedTicks(NrtStepTimer timer, uint64_t* output);
NrtResult Nrt_StepTimer_getTotalTicks(NrtStepTimer timer, uint64_t* output);
NrtResult Nrt_StepTimer_getElapsedTime(NrtStepTimer timer, NrtTimestamp* output);
NrtResult Nrt_StepTimer_getTotalTime(NrtStepTimer timer, NrtTimestamp* output);
NrtResult Nrt_StepTimer_getTargetElapsedTicks(NrtStepTimer timer, uint64_t* output);
NrtResult Nrt_StepTimer_setTargetElapsedTicks(NrtStepTimer timer, uint64_t input);
NrtResult Nrt_StepTimer_getTargetElapsedTime(NrtStepTimer timer, NrtTimestamp* output);
NrtResult Nrt_StepTimer_setTargetElapsedTime(NrtStepTimer timer, NrtTimestamp target);
NrtResult Nrt_StepTimer_getFrameCount(NrtStepTimer timer, uint32_t* output);
NrtResult Nrt_StepTimer_getFramesPerSecond(NrtStepTimer timer, uint32_t* output);
NrtResult Nrt_StepTimer_getIsFixedTimeStep(NrtStepTimer timer, int32_t* output);
NrtResult Nrt_StepTimer_setIsFixedTimeStep(NrtStepTimer timer, int32_t input);
NrtResult Nrt_StepTimer_resetElapsedTime(NrtStepTimer timer);
NrtResult Nrt_StepTimer_resetElapsedTime(NrtStepTimer timer);
NrtResult Nrt_StepTimer_tick(NrtStepTimer timer, NrtUtilitiesEventWithTimestamp event);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_STEPTIMER_H
