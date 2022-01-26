// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_INPUT_INPUTEVENTCOMPONENT_H
#define NOVELRT_ECS_INPUT_INPUTEVENTCOMPONENT_H

#ifndef NOVELRT_ECS_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.Input.h instead for the Ecs.Input namespace subset.
#endif

namespace NovelRT::Ecs::Input
{
    struct InputEventComponent
    {
        LinkedEntityListNodeComponent actionList;
        bool pressed;
        bool released;
        float mousePositionX;
        float mousePositionY;

        inline InputEventComponent& operator+=(const InputEventComponent& other) noexcept
        {
            actionList = other.actionList;
            pressed = other.pressed;
            released = other.released;
            mousePositionX = other.mousePositionX;
            mousePositionY = other.mousePositionY;
            return *this;
        };
    };
}

#endif // NOVELRT_ECS_INPUT_INPUTEVENTCOMPONENT_H
