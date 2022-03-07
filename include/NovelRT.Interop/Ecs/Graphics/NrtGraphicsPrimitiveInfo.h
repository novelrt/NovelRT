// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_GRAPHICSPRIMITIVEINFO_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_GRAPHICSPRIMITIVEINFO_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtBool Nrt_GraphicsPrimitiveInfo_Equal(NrtGraphicsPrimitiveInfo lhs, NrtGraphicsPrimitiveInfo rhs);
    NrtBool Nrt_GraphicsPrimitiveInfo_EqualRenderComponent(NrtGraphicsPrimitiveInfo lhs,
                                                           NrtRenderComponent rhs);
    NrtBool Nrt_GraphicsPrimitiveInfo_NotEqual(NrtGraphicsPrimitiveInfo lhs, NrtGraphicsPrimitiveInfo rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_GRAPHICSPRIMITIVEINFO_H
