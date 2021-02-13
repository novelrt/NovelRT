// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H
#define NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H

#include "../NrtInteropUtils.h"
#include "../NrtTransform.h"
#include "NrtKeyCode.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct BasicInteractionRectHandle* NrtBasicInteractionRect;

    NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object);
    NrtResult Nrt_Input_BasicInteractionRect_getTransform(NrtBasicInteractionRect object,
                                                          NrtTransform* outputTransform);
    NrtResult Nrt_Input_BasicInteractionRect_setTransform(NrtBasicInteractionRect object, NrtTransform transform);
    int32_t Nrt_Input_BasicInteractionRect_getLayer(NrtBasicInteractionRect object);
    NrtResult Nrt_Input_BasicInteractionRect_setLayer(NrtBasicInteractionRect object, int32_t value);
    int32_t Nrt_Input_BasicInteractionRect_getActive(NrtBasicInteractionRect object);
    NrtResult Nrt_Input_BasicInteractionRect_setActive(NrtBasicInteractionRect object, int32_t value);
    NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object);
    NrtResult Nrt_Input_BasicInteractionRect_validateInteractionPrimeter(NrtBasicInteractionRect object,
                                                                         const NrtGeoVector2F mousePosition);
    NrtKeyCodeKind Nrt_Input_BasicInteractionRect_getSubscribedKey(NrtBasicInteractionRect object);
    NrtResult Nrt_Input_BasicInteractionRect_setSubscribedKey(NrtBasicInteractionRect object, NrtKeyCodeKind value);
    NrtResult Nrt_Input_BasicInteractionRect_addInteraction(NrtBasicInteractionRect object, void (*ptr)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H
