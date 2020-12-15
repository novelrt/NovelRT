// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_INPUT_KEYSTATE_H
#define NOVELRT_INTEROP_INPUT_KEYSTATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NRT_IDLE = -1,
    NRT_KEYUP = 0,
    NRT_KEYDOWN = 1,
    NRT_KEYDOWNHELD = 2,
}  NrtKeyStateKind;

typedef int32_t NrtKeyState;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYSTATE_H
