// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtEcsGraphicsComponents.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Graphics;

NrtAtom Nrt_Components_GetRenderComponentTypeId()
{
    return GetComponentTypeId<RenderComponent>();
}
