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

int32_t Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object);
int32_t Nrt_Input_BasicInteractionRect_getTransform(NrtBasicInteractionRect object, NrtTransform* outputTransform);
int32_t Nrt_Input_BasicInteractionRect_setTransform(NrtBasicInteractionRect object, NrtTransform transform);
int32_t Nrt_Input_BasicInteractionRect_getLayer(NrtBasicInteractionRect object, int* outputValue);
int32_t Nrt_Input_BasicInteractionRect_setLayer(NrtBasicInteractionRect object, int value);
int32_t Nrt_Input_BasicInteractionRect_getActive(NrtBasicInteractionRect object, int32_t* outputValue);
int32_t Nrt_Input_BasicInteractionRect_setActive(NrtBasicInteractionRect object, int32_t value);
int32_t Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object);
int32_t Nrt_Input_BasicInteractionRect_validateInteractionPrimeter(NrtBasicInteractionRect object, const NrtGeoVector2F mousePosition);
int32_t Nrt_Input_BasicInteractionRect_getSubscribedKey(NrtBasicInteractionRect object, NrtKeyCode* outputValue);
int32_t Nrt_Input_BasicInteractionRect_setSubscribedKey(NrtBasicInteractionRect object, NrtKeyCode value);
int32_t Nrt_Input_BasicInteractionRect_addInteraction(NrtBasicInteractionRect object, void(*ptr)());
//int32_t Nrt_Input_BasicInteractionRect_removeInteraction(NrtBasicInteractionRect object, void(*ptr)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H