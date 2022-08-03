// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Timing/NrtStepTimer.h>
#include <NovelRT/Timing/StepTimer.h>
#include <NovelRT/Utilities/Event.h> // The order is important for some reason.

NrtResult Nrt_StepTimer_create(uint32_t targetFrameRate, double maxSecondDelta, NrtStepTimerHandle* output)
{
    if (output == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* timer = new NovelRT::Timing::StepTimer(targetFrameRate, maxSecondDelta);
    *output = reinterpret_cast<NrtStepTimerHandle>(timer);
    return NRT_SUCCESS;
}

uint64_t Nrt_StepTimer_getElapsedTicks(NrtStepTimerHandle timer)
{
    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    return time->getElapsedTicks();
}

uint64_t Nrt_StepTimer_getTotalTicks(NrtStepTimerHandle timer)
{
    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    return time->getTotalTicks();
}

NrtTimestamp Nrt_StepTimer_getElapsedTime(NrtStepTimerHandle timer)
{
    NovelRT::Timing::Timestamp timestamp = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer).getElapsedTime();
    return reinterpret_cast<NrtTimestamp&>(timestamp);
}

NrtTimestamp Nrt_StepTimer_getTotalTime(NrtStepTimerHandle timer)
{
    NovelRT::Timing::Timestamp timestamp = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer).getTotalTime();
    return reinterpret_cast<NrtTimestamp&>(timestamp);
}

uint64_t Nrt_StepTimer_getTargetElapsedTicks(NrtStepTimerHandle timer)
{
    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    return time->targetElapsedTicks();
}

NrtResult Nrt_StepTimer_setTargetElapsedTicks(NrtStepTimerHandle timer, uint64_t input)
{
    if (timer == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    time->targetElapsedTicks() = input;
    return NRT_SUCCESS;
}

NrtTimestamp Nrt_StepTimer_getTargetElapsedTime(NrtStepTimerHandle timer)
{
    NovelRT::Timing::Timestamp timestamp = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer).getTargetElapsedTime();
    return reinterpret_cast<NrtTimestamp&>(timestamp);
}

NrtResult Nrt_StepTimer_setTargetElapsedTime(NrtStepTimerHandle timer, NrtTimestamp target)
{
    if (timer == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    time->setTargetElapsedTime(NovelRT::Timing::Timestamp(target));
    return NRT_SUCCESS;
}

uint32_t Nrt_StepTimer_getFrameCount(NrtStepTimerHandle timer)
{
    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    return time->getFrameCount();
}

uint32_t Nrt_StepTimer_getFramesPerSecond(NrtStepTimerHandle timer)
{
    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    return time->getFramesPerSecond();
}

NrtBool Nrt_StepTimer_getIsFixedTimeStep(NrtStepTimerHandle timer)
{
    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    return time->isFixedTimeStep() ? NRT_TRUE : NRT_FALSE;
}

NrtResult Nrt_StepTimer_setIsFixedTimeStep(NrtStepTimerHandle timer, int32_t input)
{
    if (timer == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    time->isFixedTimeStep() = input;
    return NRT_SUCCESS;
}

NrtResult Nrt_StepTimer_resetElapsedTime(NrtStepTimerHandle timer)
{
    if (timer == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    time->resetElapsedTime();
    return NRT_SUCCESS;
}

NrtResult Nrt_StepTimer_tick(NrtStepTimerHandle timer, NrtUtilitiesEventWithTimestampHandle event)
{
    if (event == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* time = reinterpret_cast<NovelRT::Timing::StepTimer*>(timer);
    auto* eventWithTimestamp = reinterpret_cast<NovelRT::Utilities::Event<NovelRT::Timing::Timestamp>*>(event);
    time->tick(*eventWithTimestamp);
    return NRT_SUCCESS;
}
