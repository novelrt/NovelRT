// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_INPUT_INPUTEVENTCOMPONENT_H
#define NOVELRT_INTEROP_ECS_INPUT_INPUTEVENTCOMPONENT_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void Nrt_InputEventComponent_PlusEquals_Operator(NrtInputEventComponent* lhs, NrtInputEventComponent rhs);
    NrtBool Nrt_InputEventComponent_Equals_Operator(NrtInputEventComponent lhs, NrtInputEventComponent rhs);

#ifdef __cplusplus
}
#endif


#endif // NOVELRT_INTEROP_ECS_INPUT_INPUTEVENTCOMPONENT_H
