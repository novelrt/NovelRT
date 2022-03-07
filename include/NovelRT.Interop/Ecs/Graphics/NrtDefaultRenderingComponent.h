// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGCOMPONENT_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGCOMPONENT_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void Nrt_RenderComponent_AddAssignRenderComponent(NrtRenderComponent* lhs, NrtRenderComponent rhs);
    NrtBool Nrt_RenderComponent_Equal(NrtRenderComponent lhs, NrtRenderComponent rhs);
    NrtBool Nrt_RenderComponent_NotEqual(NrtRenderComponent lhs, NrtRenderComponent rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGCOMPONENT_H
