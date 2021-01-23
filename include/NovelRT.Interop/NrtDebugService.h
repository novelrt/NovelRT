// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_DEBUGSERVICE_H
#define NOVELRT_INTEROP_DEBUGSERVICE_H

#include "Graphics/NrtRenderingService.h"
#include "Utilities/NrtCommonEvents.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct DebugServiceHandle* NrtDebugService;

    NrtResult Nrt_DebugService_create(NrtUtilitiesEvent sceneConstructionEvent,
                                      NrtRenderingService renderingService,
                                      NrtDebugService* outputService);
    NrtBool Nrt_DebugService_getIsFpsCounterVisible(NrtDebugService service);
    NrtResult Nrt_DebugService_setIsFpsCounterVisible(NrtDebugService service, int32_t value);
    uint32_t Nrt_DebugService_getFramesPerSecond(NrtDebugService service);
    NrtResult Nrt_DebugService_setFramesPerSecond(NrtDebugService service, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DEBUGSERVICE_H
