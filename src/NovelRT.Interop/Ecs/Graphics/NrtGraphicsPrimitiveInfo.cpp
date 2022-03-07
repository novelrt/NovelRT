// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtGraphicsPrimitiveInfo.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
extern "C"
{
    using namespace NovelRT::Ecs::Graphics;

#endif

    NrtBool Nrt_GraphicsPrimitiveInfo_Equal(NrtGraphicsPrimitiveInfo lhs, NrtGraphicsPrimitiveInfo rhs)
    {
        return *reinterpret_cast<const GraphicsPrimitiveInfo*>(&lhs) ==
               *reinterpret_cast<const GraphicsPrimitiveInfo*>(&rhs);
    }
    NrtBool Nrt_GraphicsPrimitiveInfo_EqualRenderComponent(NrtGraphicsPrimitiveInfo lhs,
                                                                           NrtRenderComponent rhs)
    {
        return *reinterpret_cast<const GraphicsPrimitiveInfo*>(&lhs) == *reinterpret_cast<const RenderComponent*>(&rhs);
    }
    NrtBool Nrt_GraphicsPrimitiveInfo_NotEqual(NrtGraphicsPrimitiveInfo lhs, NrtGraphicsPrimitiveInfo rhs)
    {
        return *reinterpret_cast<const GraphicsPrimitiveInfo*>(&lhs) !=
               *reinterpret_cast<const GraphicsPrimitiveInfo*>(&rhs);
    }

#ifdef __cplusplus
}
#endif
