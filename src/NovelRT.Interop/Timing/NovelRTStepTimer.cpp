// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/Timing/NovelRTStepTimer.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
extern "C" {
#endif

NovelRTResult NovelRT_StepTimer_create(uint32_t targetFrameRate, double maxSecondDelta, NovelRTStepTimer* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer timer = NovelRT::Timing::StepTimer(targetFrameRate, maxSecondDelta);
    *output = reinterpret_cast<NovelRTStepTimer>(&timer);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getElapsedTicks(NovelRTStepTimer timer, uint64_t* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    *output = time.getElapsedTicks();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getTotalTicks(NovelRTStepTimer timer, uint64_t* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    *output = time.getTotalTicks();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getElapsedTime(NovelRTStepTimer timer, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer).getElapsedTime();
    *output = reinterpret_cast<NovelRTTimestamp&>(time);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getTotalTime(NovelRTStepTimer timer, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer).getTotalTime();
    *output = reinterpret_cast<NovelRTTimestamp&>(time);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getTargetElapsedTicks(NovelRTStepTimer timer, uint64_t* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    *output = time.targetElapsedTicks();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_setTargetElapsedTicks(NovelRTStepTimer timer, uint64_t input, const char** errorMessage) {
    if (timer == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    time.targetElapsedTicks() = input;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getTargetElapsedTime(NovelRTStepTimer timer, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer).getTargetElapsedTime();
    *output = reinterpret_cast<NovelRTTimestamp&>(time);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_setTargetElapsedTime(NovelRTStepTimer timer, NovelRTTimestamp target, const char** errorMessage) {
    if (timer == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    time.setTargetElapsedTime(reinterpret_cast<NovelRT::Timing::Timestamp&>(target));
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getFrameCount(NovelRTStepTimer timer, uint32_t* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    *output = time.getFrameCount();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getFramesPerSecond(NovelRTStepTimer timer, uint32_t* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    *output = time.getFramesPerSecond();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_getIsFixedTimeStep(NovelRTStepTimer timer, NovelRTBool* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    *output = time.isFixedTimeStep();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_setIsFixedTimeStep(NovelRTStepTimer timer, NovelRTBool input, const char** errorMessage) {
    if (timer == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    time.isFixedTimeStep() = input;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_resetElapsedTime(NovelRTStepTimer timer, const char** errorMessage) {
    if (timer == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    time.resetElapsedTime();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_StepTimer_tick(NovelRTStepTimer timer, NovelRTUpdateEventWithTimestamp event, const char** errorMessage) {
    if (event == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::StepTimer time = reinterpret_cast<NovelRT::Timing::StepTimer&>(timer);
    NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> eventWithTimestamp = reinterpret_cast<NovelRT::Utilities::Event<NovelRT::Timing::Timestamp>&>(event);
    time.tick(eventWithTimestamp);
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif