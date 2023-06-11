// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcsComponents.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;

NrtAtom Nrt_Components_GetTransformComponentTypeId()
{
    return GetComponentTypeId<TransformComponent>();
}
NrtAtom Nrt_Components_GetEntityGraphComponentTypeId()
{
    return GetComponentTypeId<EntityGraphComponent>();
}
NrtAtom Nrt_Components_LinkedEntityListNodeComponentTypeId()
{
    return GetComponentTypeId<LinkedEntityListNodeComponent>();
}
