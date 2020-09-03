// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Utilities/NovelRTEvents.h"

#ifdef __cplusplus
extern "C" {
#endif

NovelRTResult NovelRT_Events_getNovelRunnerUpdateEvent(NovelRTNovelRunner runner, NovelRTUpdateEventWithTimestamp* outputEvent, const char** errorMessage) {
    if (runner == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::NovelRunner* cRunner = reinterpret_cast<NovelRT::NovelRunner*>(runner);
    *outputEvent = reinterpret_cast<NovelRTUpdateEventWithTimestamp&>(cRunner->Update);
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif