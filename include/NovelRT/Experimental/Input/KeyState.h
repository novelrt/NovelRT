// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_KEYSTATE_H
#define NOVELRT_EXPERIMENTAL_INPUT_KEYSTATE_H

#ifndef NOVELRT_EXPERIMENTAL_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Experimental::Input
{
    /**
     * @brief A set of key states.
     */
    enum class KeyState : int32_t
    {
        Idle = -1,
        KeyUp = 0,
        KeyDown = 1,
        KeyDownHeld = 2
    };
}

#endif // !NOVELRT_EXPERIMENTAL_INPUT_KEYSTATE_H