// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_INPUT_KEYSTATE_H
#define NOVELRT_INTEROP_INPUT_KEYSTATE_H

#ifdef __cplusplus
extern "C" {
#endif

enum NovelRTKeyState {
    Idle = -1,
    KeyUp = 0,
    KeyDown = 1,
    KeyDownHeld = 2,
};

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYSTATE_H