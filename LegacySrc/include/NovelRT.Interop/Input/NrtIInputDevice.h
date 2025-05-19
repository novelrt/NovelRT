// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_INPUT_NRTIINPUTDEVICE_H
#define NOVELRT_INTEROP_INPUT_NRTIINPUTDEVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_IInputDevice_Destroy(NrtIInputDeviceHandle device);

    NrtBool Nrt_IInputDevice_IsKeyPressed(NrtIInputDeviceHandle device, const char* key);
    NrtBool Nrt_IInputDevice_IsKeyHeld(NrtIInputDeviceHandle device, const char* key);
    NrtBool Nrt_IInputDevice_IsKeyReleased(NrtIInputDeviceHandle device, const char* key);
    NrtKeyState Nrt_IInputDevice_GetKeyState(NrtIInputDeviceHandle device, const char* key);

    NrtResult Nrt_IInputDevice_AddInputAction(NrtIInputDeviceHandle device,
                                              const char* actionName,
                                              const char* keyIdentifier,
                                              NrtInputActionHandle* outputAction);

    NrtResult Nrt_IInputDevice_GetAvailableKey(NrtIInputDeviceHandle device,
                                               const char* requestedKey,
                                               NrtNovelKeyHandle* outputKey);

    NrtGeoVector2F Nrt_IInputDevice_GetMousePosition(NrtIInputDeviceHandle device);

    NrtInputActionList Nrt_IInputDevice_GetAllMappings(NrtIInputDeviceHandle device);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_NRTIINPUTDEVICE_H
