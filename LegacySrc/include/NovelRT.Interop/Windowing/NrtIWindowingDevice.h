// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_WINDOWING_NRTIWINDOWINGDEVICE_H
#define NOVELRT_INTEROP_WINDOWING_NRTIWINDOWINGDEVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IWindowingDevice_Destroy(NrtIWindowingDeviceHandle device);
    NrtBool Nrt_IWindowingDevice_GetIsVisible(NrtIWindowingDeviceHandle device);
    NrtBool Nrt_IWindowingDevice_GetShouldClose(NrtIWindowingDeviceHandle device);
    // The returned string is allocated, remember to free it!
    char* Nrt_IWindowingDevice_GetWindowTitle(NrtIWindowingDeviceHandle device);
    NrtResult Nrt_IWindowingDevice_SetWindowTitle(NrtIWindowingDeviceHandle device, const char* newTitle);
    NrtResult Nrt_IWindowingDevice_ProcessAllMessages(NrtIWindowingDeviceHandle device);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_WINDOWING_NRTIWINDOWINGDEVICE_H
