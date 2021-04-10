// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
#define NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtWindowingServiceHandle Nrt_WindowingService_create();

    NrtResult Nrt_WindowingService_initialiseWindow(NrtWindowingServiceHandle service,
                                                    int32_t displayNumber,
                                                    const char* windowTitle,
                                                    NrtWindowMode windowMode,
                                                    int32_t transparencyEnabled);
    NrtResult Nrt_WindowingService_tearDown(NrtWindowingServiceHandle service);
    const char* Nrt_WindowingService_getWindowTitle(NrtWindowingServiceHandle service);
    NrtResult Nrt_WindowingService_setWindowTitle(NrtWindowingServiceHandle service, const char* value);
    NrtResult Nrt_WindowingService_setWindowSize(NrtWindowingServiceHandle service, NrtGeoVector2F value);
    NrtGeoVector2F Nrt_WindowingService_getWindowSize(NrtWindowingServiceHandle service);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
