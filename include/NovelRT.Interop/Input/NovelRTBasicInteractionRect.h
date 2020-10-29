// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTTransform.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Input/NovelRTKeyCode.h"
#ifndef NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H
#define NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BasicInteractionRectHandle* NovelRTBasicInteractionRect;

int32_t NovelRT_Input_BasicInteractionRect_executeObjectBehaviour(NovelRTBasicInteractionRect object);
int32_t NovelRT_Input_BasicInteractionRect_getTransform(NovelRTBasicInteractionRect object, NovelRTTransform* outputTransform);
int32_t NovelRT_Input_BasicInteractionRect_setTransform(NovelRTBasicInteractionRect object, NovelRTTransform transform);
int32_t NovelRT_Input_BasicInteractionRect_getLayer(NovelRTBasicInteractionRect object, int* outputValue);
int32_t NovelRT_Input_BasicInteractionRect_setLayer(NovelRTBasicInteractionRect object, int value);
int32_t NovelRT_Input_BasicInteractionRect_getActive(NovelRTBasicInteractionRect object, int32_t* outputValue);
int32_t NovelRT_Input_BasicInteractionRect_setActive(NovelRTBasicInteractionRect object, int32_t value);
int32_t NovelRT_Input_BasicInteractionRect_executeObjectBehaviour(NovelRTBasicInteractionRect object);
int32_t NovelRT_Input_BasicInteractionRect_validateInteractionPrimeter(NovelRTBasicInteractionRect object, const NovelRTGeoVector2F mousePosition);
int32_t NovelRT_Input_BasicInteractionRect_getSubscribedKey(NovelRTBasicInteractionRect object, NovelRTKeyCode* outputValue);
int32_t NovelRT_Input_BasicInteractionRect_setSubscribedKey(NovelRTBasicInteractionRect object, NovelRTKeyCode value);
int32_t NovelRT_Input_BasicInteractionRect_addInteraction(NovelRTBasicInteractionRect object, void(*ptr)());
//int32_t NovelRT_Input_BasicInteractionRect_removeInteraction(NovelRTBasicInteractionRect object, void(*ptr)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H