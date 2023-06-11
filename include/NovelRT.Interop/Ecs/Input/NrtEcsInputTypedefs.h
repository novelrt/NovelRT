// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_INPUT_NRTECSINPUTTYPEDEFS_H
#define NOVELRT_INTEROP_ECS_INPUT_NRTECSINPUTTYPEDEFS_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // Components
    // Note that int32_t is used instead of NrtKeyState, as, in C,
    // enums are *not* guaranteed to be exactly the size of an int.
    // Even though it is in 99.99% of the cases due to system ABI,
    // we better enforce the size given by the C++ NovelRT API.
    // See KeyState definition:
    //     enum class KeyState : int32_t <---

    typedef struct {
        NrtAtom actionId;
        // Uses the NrtKeyState enum.
        int32_t state;
        float mousePositionX;
        float mousePositionY;
    } NrtInputEventComponent;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_INPUT_NRTECSINPUTTYPEDEFS_H
