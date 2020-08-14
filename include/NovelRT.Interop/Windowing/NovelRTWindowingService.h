// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"

#ifndef NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H
#define NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct WindowingServiceHandle* NovelRTWindowingService;

NovelRTWindowingService WindowingService_create();

NovelRTResult NovelRT_WindowingService_initialiseWindow(NovelRTWindowingService service, int displayNumber, const char* windowTitle, bool transparencyEnabled, const char** errorMessage);
NovelRTResult NovelRT_WindowingService_tearDown(NovelRTWindowingService service, const char** errorMessage);
NovelRTResult NovelRT_WindowingService_getWindowTitle(NovelRTWindowingService service, const char** windowTitle, const char** errorMessage);
NovelRTResult NovelRT_WindowingService_setWindowTitle(NovelRTWindowingService service, const char* value, const char** errorMessage);
NovelRTResult NovelRT_WindowingService_setWindowSize(NovelRTWindowingService service, NovelRTGeoVector2F value, const char** errorMessage);
NovelRTResult NovelRT_WindowingService_getWindowSize(NovelRTWindowingService service, NovelRTGeoVector2F* output, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_WINDOWING_WINDOWINGSERVICE_H