// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_DEBUGSERVICE_H
#define NOVELRT_INTEROP_DEBUGSERVICE_H

#include "NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_DebugService_create(NrtUtilitiesEventHandle sceneConstructionEvent,
                                      NrtRenderingServiceHandle renderingService,
                                      NrtDebugServiceHandle* outputService);
    NrtBool Nrt_DebugService_getIsFpsCounterVisible(NrtDebugServiceHandle service);
    NrtResult Nrt_DebugService_setIsFpsCounterVisible(NrtDebugServiceHandle service, int32_t value);
    uint32_t Nrt_DebugService_getFramesPerSecond(NrtDebugServiceHandle service);
    NrtResult Nrt_DebugService_setFramesPerSecond(NrtDebugServiceHandle service, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DEBUGSERVICE_H
