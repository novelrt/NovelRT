// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Utilities/NovelRTCommonEvents.h"
#include "NovelRT.Interop/Graphics/NovelRTRenderingService.h"

#ifndef NOVELRT_INTEROP_DEBUGSERVICE_H
#define NOVELRT_INTEROP_DEBUGSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DebugServiceHandle* NovelRTDebugService;

int32_t NovelRT_DebugService_create(NovelRTUtilitiesEvent sceneConstructionEvent, NovelRTRenderingService renderingService, NovelRTDebugService* outputService, const char** errorMessage);
int32_t NovelRT_DebugService_getIsFpsCounterVisible(NovelRTDebugService service, int32_t* result, const char** errorMessage);
int32_t NovelRT_DebugService_setIsFpsCounterVisible(NovelRTDebugService service, int32_t value, const char** errorMessage);
int32_t NovelRT_DebugService_getFramesPerSecond(NovelRTDebugService service, uint32_t* outputValue, const char** errorMessage);
int32_t NovelRT_DebugService_setFramesPerSecond(NovelRTDebugService service, uint32_t value, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DEBUGSERVICE_H
