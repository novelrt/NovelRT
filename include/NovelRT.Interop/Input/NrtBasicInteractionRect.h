// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H
#define NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRectHandle object);
    NrtResult Nrt_Input_BasicInteractionRect_getTransform(NrtBasicInteractionRectHandle object,
                                                          NrtTransform* outputTransform);
    NrtResult Nrt_Input_BasicInteractionRect_setTransform(NrtBasicInteractionRectHandle object, NrtTransform transform);
    int32_t Nrt_Input_BasicInteractionRect_getLayer(NrtBasicInteractionRectHandle object);
    NrtResult Nrt_Input_BasicInteractionRect_setLayer(NrtBasicInteractionRectHandle object, int32_t value);
    int32_t Nrt_Input_BasicInteractionRect_getActive(NrtBasicInteractionRectHandle object);
    NrtResult Nrt_Input_BasicInteractionRect_setActive(NrtBasicInteractionRectHandle object, int32_t value);
    NrtResult Nrt_Input_BasicInteractionRect_validateInteractionPrimeter(NrtBasicInteractionRectHandle object,
                                                                         const NrtGeoVector2F mousePosition);
    NrtKeyCodeKind Nrt_Input_BasicInteractionRect_getSubscribedKey(NrtBasicInteractionRectHandle object);
    NrtResult Nrt_Input_BasicInteractionRect_setSubscribedKey(NrtBasicInteractionRectHandle object,
                                                              NrtKeyCodeKind value);
    NrtResult Nrt_Input_BasicInteractionRect_addInteraction(NrtBasicInteractionRectHandle object, void (*ptr)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_BASICINTERACTIONRECT_H
