// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_KEYSTATE_H
#define NOVELRT_INPUT_KEYSTATE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input
{
    /**
     * @brief A set of key states.
     */
    enum class KeyState : int32_t
    {
        Idle = -1,
        KeyUp = GLFW_RELEASE,      // 0
        KeyDown = GLFW_PRESS,      // 1
        KeyDownHeld = GLFW_REPEAT, // 2
    };
}

#endif // !NOVELRT_INPUT_KEYSTATE_H
