// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/Utilities/NovelRTEvents.h"

#ifndef NOVELRT_INTEROP_TIMING_STEPTIMER_H
#define NOVELRT_INTEROP_TIMING_STEPTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StepTimerHandle* NovelRTStepTimer;

NovelRTResult NovelRT_StepTimer_create(uint32_t targetFrameRate, double maxSecondDelta, NovelRTStepTimer* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getElapsedTicks(NovelRTStepTimer timer, uint64_t* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getTotalTicks(NovelRTStepTimer timer, uint64_t* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getElapsedTime(NovelRTStepTimer timer, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getTotalTime(NovelRTStepTimer timer, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getTargetElapsedTicks(NovelRTStepTimer timer, uint64_t* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_setTargetElapsedTicks(NovelRTStepTimer timer, uint64_t input, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getTargetElapsedTime(NovelRTStepTimer timer, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_setTargetElapsedTime(NovelRTStepTimer timer, NovelRTTimestamp target, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getFrameCount(NovelRTStepTimer timer, uint32_t* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getFramesPerSecond(NovelRTStepTimer timer, uint32_t* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_getIsFixedTimeStep(NovelRTStepTimer timer, NovelRTBool* output, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_setIsFixedTimeStep(NovelRTStepTimer timer, NovelRTBool input, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_resetElapsedTime(NovelRTStepTimer timer, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_resetElapsedTime(NovelRTStepTimer timer, const char** errorMessage);
NovelRTResult NovelRT_StepTimer_tick(NovelRTStepTimer timer, NovelRTUpdateEventWithTimestamp event, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_STEPTIMER_H
