// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
#define NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H

#include "../Maths/NrtGeoVector2F.h"
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef uint32_t NrtWindowMode;

    enum NrtWindowModeKind
    {
        NRT_WINDOW_MODE_WINDOWED = 0,
        NRT_WINDOW_MODE_BORDERLESS = 1,
        NRT_WINDOW_MODE_FULLSCREEN = 2
    };

    typedef struct WindowingServiceHandle* NrtWindowingService;

    NrtWindowingService Nrt_WindowingService_create();

    NrtResult Nrt_WindowingService_initialiseWindow(NrtWindowingService service,
                                                    int32_t displayNumber,
                                                    const char* windowTitle,
                                                    NrtWindowMode windowMode,
                                                    int32_t transparencyEnabled);
    NrtResult Nrt_WindowingService_tearDown(NrtWindowingService service);
    const char* Nrt_WindowingService_getWindowTitle(NrtWindowingService service);
    NrtResult Nrt_WindowingService_setWindowTitle(NrtWindowingService service, const char* value);
    NrtResult Nrt_WindowingService_setWindowSize(NrtWindowingService service, NrtGeoVector2F value);
    NrtGeoVector2F Nrt_WindowingService_getWindowSize(NrtWindowingService service);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
