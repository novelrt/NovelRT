// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtDefaultRenderingComponent.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void Nrt_RenderComponent_PlusEquals_Operator(NrtRenderComponent* lhs, NrtRenderComponent rhs)
    {
        *reinterpret_cast<NovelRT::Ecs::Graphics::RenderComponent*>(lhs) +=
            *reinterpret_cast<const NovelRT::Ecs::Graphics::RenderComponent*>(&rhs);
    }

    NrtBool Nrt_RenderComponent_Equals_Operator(NrtRenderComponent lhs, NrtRenderComponent rhs)
    {
        return *reinterpret_cast<const NovelRT::Ecs::Graphics::RenderComponent*>(&lhs) ==
            *reinterpret_cast<const NovelRT::Ecs::Graphics::RenderComponent*>(&rhs);
    }

    NrtBool Nrt_RenderComponent_NotEquals_Operator(NrtRenderComponent lhs, NrtRenderComponent rhs)
    {
        return *reinterpret_cast<const NovelRT::Ecs::Graphics::RenderComponent*>(&lhs) !=
            *reinterpret_cast<const NovelRT::Ecs::Graphics::RenderComponent*>(&rhs);
    }

#ifdef __cplusplus
}
#endif
