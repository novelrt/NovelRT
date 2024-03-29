// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_INPUT_H
#define NOVELRT_ECS_INPUT_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

#include <NovelRT/Input/IInputDevice.hpp>
#include <NovelRT/Input/InputAction.hpp>
#include <NovelRT/Input/KeyState.hpp>
#include <NovelRT/Input/KeyStateFrameChangeLog.hpp>
#include <NovelRT/Input/NovelKey.hpp>
#include <map>

namespace NovelRT::Ecs::Input
{
    class InputSystem;
    struct InputEventComponent;
}

#include "InputEventComponent.h"
#include "InputSystem.h"

#endif // NOVELRT_ECS_INPUT_H
