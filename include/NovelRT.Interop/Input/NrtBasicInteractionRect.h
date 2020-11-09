// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H
#define NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H

#include "../NrtTransform.h"
#include "../NrtInteropUtils.h"
#include "NrtKeyCode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BasicInteractionRectHandle* NrtBasicInteractionRect;

NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object);
NrtResult Nrt_Input_BasicInteractionRect_getTransform(NrtBasicInteractionRect object, NrtTransform* outputTransform);
NrtResult Nrt_Input_BasicInteractionRect_setTransform(NrtBasicInteractionRect object, NrtTransform transform);
NrtResult Nrt_Input_BasicInteractionRect_getLayer(NrtBasicInteractionRect object, int* outputValue);
NrtResult Nrt_Input_BasicInteractionRect_setLayer(NrtBasicInteractionRect object, int value);
NrtResult Nrt_Input_BasicInteractionRect_getActive(NrtBasicInteractionRect object, int32_t* outputValue);
NrtResult Nrt_Input_BasicInteractionRect_setActive(NrtBasicInteractionRect object, int32_t value);
NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object);
NrtResult Nrt_Input_BasicInteractionRect_validateInteractionPrimeter(NrtBasicInteractionRect object, const NrtGeoVector2F mousePosition);
NrtResult Nrt_Input_BasicInteractionRect_getSubscribedKey(NrtBasicInteractionRect object, NrtKeyCodeKind* outputValue);
NrtResult Nrt_Input_BasicInteractionRect_setSubscribedKey(NrtBasicInteractionRect object, NrtKeyCodeKind value);
NrtResult Nrt_Input_BasicInteractionRect_addInteraction(NrtBasicInteractionRect object, void(*ptr)());
//NrtResult Nrt_Input_BasicInteractionRect_removeInteraction(NrtBasicInteractionRect object, void(*ptr)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H