// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_INPUT_H
#define NOVELRT_ECS_INPUT_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

#include "../../Input/Input.h"
#include <map>

namespace NovelRT::Ecs::Input
{
    class InputSystem;
    struct InputEventComponent;
}

#include "InputSystem.h"
#include "InputEventComponent.h"

#endif // NOVELRT_ECS_INPUT_H
