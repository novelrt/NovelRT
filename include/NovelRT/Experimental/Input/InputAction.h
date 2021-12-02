// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_INPUTACTION_H
#define NOVELRT_EXPERIMENTAL_INPUT_INPUTACTION_H

#ifndef NOVELRT_EXPERIMENTAL_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Experimental::Input
{
    struct InputAction
    {
        std::string actionName;
        NovelKey pairedKey;
        bool isPressed = false;
        bool isHeld = false;
        bool isReleased = false;
    };
}

#endif // NOVELRT_EXPERIMENTAL_INPUT_INPUTACTION_H
