// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"

#ifndef NOVELRT_INTEROP_UTILITIES_EVENTS_H
#define NOVELRT_INTEROP_UTILITIES_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UpdateEventWithTimestampHandle* NovelRTUpdateEventWithTimestamp;

NovelRTResult NovelRT_Events_getNovelRunnerUpdateEvent(NovelRTNovelRunner runner, NovelRTUpdateEventWithTimestamp* outputEvent, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_UTILITIES_EVENTS_H
