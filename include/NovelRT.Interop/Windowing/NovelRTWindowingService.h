// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"

#ifndef NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
#define NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct WindowingServiceHandle* NovelRTWindowingService;

NovelRTWindowingService WindowingService_create() noexcept;

void WindowingService_initialiseWindow(NovelRTWindowingService service, int displayNumber, const char* windowTitle, bool transparencyEnabled);
void WindowingService_tearDown(NovelRTWindowingService service);
const char* WindowingService_getWindowTitle(NovelRTWindowingService service);
void WindowingService_setWindowTitle(NovelRTWindowingService service, const char* value);
void WindowingService_setWindowSize(NovelRTWindowingService service, const NovelRTGeoVector2F& value);
NovelRTGeoVector2F WindowingService_getWindowSize(NovelRTWindowingService service);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H