// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_INPUT_NRTINPUTTYPEDEFS_H
#define NOVELRT_INTEROP_INPUT_NRTINPUTTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtIInputDevice* NrtIInputDeviceHandle;
    typedef struct NrtInputAction* NrtInputActionHandle;
    typedef struct NrtNovelKey* NrtNovelKeyHandle;

    typedef enum
    {
        Idle = 0,
        KeyUp = 1,
        KeyDown = 2,
        KeyDownHeld = 3
    } NrtKeyState;

    typedef struct
    {
        NrtInputActionHandle begin;
        NrtInputActionHandle end;
        intptr_t increment;
    } NrtInputActionList;

    // Info-structs: those serve as a convenient read-only model for the C API, without
    // needing to call each getter separately.

    typedef struct
    {
        const char* keyName;
        int32_t externalKeyCode;
        int32_t externalModifierCode;
    } NrtNovelKeyInfo;

    typedef struct
    {
        const char* actionName;
        NrtNovelKeyInfo pairedKey;
        NrtKeyState state;
    } NrtInputActionInfo;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_NRTINPUTTYPEDEFS_H
