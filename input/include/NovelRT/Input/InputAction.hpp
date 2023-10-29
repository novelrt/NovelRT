// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_INPUTACTION_H
#define NOVELRT_INPUT_INPUTACTION_H

namespace NovelRT::Input
{
    struct InputAction
    {
        std::string actionName;
        NovelKey pairedKey;
        KeyState state = KeyState::Idle;
    };
}

#endif // NOVELRT_INPUT_INPUTACTION_H
