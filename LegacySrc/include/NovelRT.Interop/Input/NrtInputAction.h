// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_INPUT_NRTINPUTACTION_H
#define NOVELRT_INTEROP_INPUT_NRTINPUTACTION_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    NrtInputActionInfo Nrt_InputAction_ReadAsInfo(NrtInputActionHandle action);
    intptr_t Nrt_InputActionList_IncrementSize();

    const char* Nrt_InputAction_GetActionName(NrtInputActionHandle action);
    NrtNovelKeyHandle Nrt_InputAction_GetPairedKey(NrtInputActionHandle action);
    NrtKeyState Nrt_InputAction_GetState(NrtInputActionHandle action);
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_NRTINPUTACTION_H
