// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_TIMING_STEPTIMER_H
#define NOVELRT_INTEROP_TIMING_STEPTIMER_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_StepTimer_create(uint32_t targetFrameRate, double maxSecondDelta, NrtStepTimerHandle* output);
    uint64_t Nrt_StepTimer_getElapsedTicks(NrtStepTimerHandle timer);
    uint64_t Nrt_StepTimer_getTotalTicks(NrtStepTimerHandle timer);
    NrtTimestamp Nrt_StepTimer_getElapsedTime(NrtStepTimerHandle timer);
    NrtTimestamp Nrt_StepTimer_getTotalTime(NrtStepTimerHandle timer);
    uint64_t Nrt_StepTimer_getTargetElapsedTicks(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_setTargetElapsedTicks(NrtStepTimerHandle timer, uint64_t input);
    NrtTimestamp Nrt_StepTimer_getTargetElapsedTime(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_setTargetElapsedTime(NrtStepTimerHandle timer, NrtTimestamp target);
    uint32_t Nrt_StepTimer_getFrameCount(NrtStepTimerHandle timer);
    uint32_t Nrt_StepTimer_getFramesPerSecond(NrtStepTimerHandle timer);
    NrtBool Nrt_StepTimer_getIsFixedTimeStep(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_setIsFixedTimeStep(NrtStepTimerHandle timer, int32_t input);
    NrtResult Nrt_StepTimer_resetElapsedTime(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_tick(NrtStepTimerHandle timer, NrtUtilitiesEventWithTimestampHandle event);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_STEPTIMER_H
