// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_TIMING_STEPTIMER_H
#define NOVELRT_INTEROP_TIMING_STEPTIMER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_StepTimer_Create(uint32_t targetFrameRate, double maxSecondDelta, NrtStepTimerHandle* output);
    uint64_t Nrt_StepTimer_GetElapsedTicks(NrtStepTimerHandle timer);
    uint64_t Nrt_StepTimer_GetTotalTicks(NrtStepTimerHandle timer);
    NrtTimestamp Nrt_StepTimer_GetElapsedTime(NrtStepTimerHandle timer);
    NrtTimestamp Nrt_StepTimer_GetTotalTime(NrtStepTimerHandle timer);
    uint64_t Nrt_StepTimer_GetTargetElapsedTicks(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_SetTargetElapsedTicks(NrtStepTimerHandle timer, uint64_t input);
    NrtTimestamp Nrt_StepTimer_GetTargetElapsedTime(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_SetTargetElapsedTime(NrtStepTimerHandle timer, NrtTimestamp target);
    uint32_t Nrt_StepTimer_GetFrameCount(NrtStepTimerHandle timer);
    uint32_t Nrt_StepTimer_GetFramesPerSecond(NrtStepTimerHandle timer);
    NrtBool Nrt_StepTimer_GetIsFixedTimeStep(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_SetIsFixedTimeStep(NrtStepTimerHandle timer, int32_t input);
    NrtResult Nrt_StepTimer_ResetElapsedTime(NrtStepTimerHandle timer);
    NrtResult Nrt_StepTimer_Tick(NrtStepTimerHandle timer, NrtUtilitiesEventWithTimestampHandle event);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_STEPTIMER_H
