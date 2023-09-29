// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_INPUTACTION_H
#define NOVELRT_INPUT_INPUTACTION_H

#ifndef NOVELRT_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Input
{
    struct InputAction
    {
        std::string actionName;
        NovelKey pairedKey;
        KeyState state = KeyState::Idle;
    };

    inline bool operator==(InputAction const& lhs, InputAction const& rhs) noexcept
    {
        return lhs.state == rhs.state && (lhs.pairedKey == rhs.pairedKey) && lhs.actionName == rhs.actionName;
    }

    inline bool operator!=(const InputAction& lhs, const InputAction& rhs) noexcept
    {
        return (lhs.state != rhs.state) || (lhs.pairedKey != rhs.pairedKey) || (lhs.actionName != rhs.actionName);
    }


}

#endif // NOVELRT_INPUT_INPUTACTION_H
