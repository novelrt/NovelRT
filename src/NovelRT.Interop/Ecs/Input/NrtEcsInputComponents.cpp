// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Input/NrtEcsInputComponents.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Input;

NrtAtom Nrt_Components_GetInputEventComponentTypeId()
{
    return GetComponentTypeId<InputEventComponent>();
}
