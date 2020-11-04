// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
#define NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H

#include "../Maths/NrtGeoVector2F.h"
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WindowingServiceHandle* NrtWindowingService;

NrtWindowingService Nrt_WindowingService_create();

int32_t Nrt_WindowingService_initialiseWindow(NrtWindowingService service, int displayNumber, const char* windowTitle, int32_t transparencyEnabled);
int32_t Nrt_WindowingService_tearDown(NrtWindowingService service);
int32_t Nrt_WindowingService_getWindowTitle(NrtWindowingService service, const char** windowTitle);
int32_t Nrt_WindowingService_setWindowTitle(NrtWindowingService service, const char* value);
int32_t Nrt_WindowingService_setWindowSize(NrtWindowingService service, NrtGeoVector2F value);
int32_t Nrt_WindowingService_getWindowSize(NrtWindowingService service, NrtGeoVector2F* output);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H