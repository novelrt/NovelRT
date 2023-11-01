// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <cstdint>
#include <NovelRT/Input/KeyState.hpp>

namespace NovelRT::Input
{
    class KeyStateFrameChangeLog
    {

    private:
        KeyState _currentState = KeyState::Idle;
        uint32_t _changeCount = 0;

    public:
        void PushNewState(KeyState newState) noexcept;
        KeyState GetCurrentState() const noexcept;
        uint32_t GetChangeCount() const noexcept;
    };
}

