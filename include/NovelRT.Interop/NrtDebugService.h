// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_DEBUGSERVICE_H
#define NOVELRT_INTEROP_DEBUGSERVICE_H

#include "Utilities/NrtCommonEvents.h"
#include "Graphics/NrtRenderingService.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DebugServiceHandle* NrtDebugService;

int32_t Nrt_DebugService_create(NrtUtilitiesEvent sceneConstructionEvent, NrtRenderingService renderingService, NrtDebugService* outputService);
int32_t Nrt_DebugService_getIsFpsCounterVisible(NrtDebugService service, int32_t* result);
int32_t Nrt_DebugService_setIsFpsCounterVisible(NrtDebugService service, int32_t value);
int32_t Nrt_DebugService_getFramesPerSecond(NrtDebugService service, uint32_t* outputValue);
int32_t Nrt_DebugService_setFramesPerSecond(NrtDebugService service, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DEBUGSERVICE_H
