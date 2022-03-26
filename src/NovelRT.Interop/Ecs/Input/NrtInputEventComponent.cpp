// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Input/NrtInputEventComponent.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs::Input;

#ifdef __cplusplus
extern "C"
{
#endif

    void Nrt_InputEventComponent_AddAssignInputEventComponent(NrtInputEventComponent* lhs, NrtInputEventComponent rhs)
    {
        *reinterpret_cast<struct InputEventComponent*>(lhs) +=
            *reinterpret_cast<const struct InputEventComponent*>(&rhs);
    };

    NrtBool Nrt_InputEventComponent_Equal(NrtInputEventComponent lhs, NrtInputEventComponent rhs)
    {
        return *reinterpret_cast<const InputEventComponent*>(&lhs) ==
            *reinterpret_cast<const InputEventComponent*>(&rhs);
    }

#ifdef __cplusplus
}
#endif
