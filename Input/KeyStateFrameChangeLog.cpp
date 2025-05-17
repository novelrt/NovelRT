// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Input/KeyStateFrameChangeLog.hpp>

namespace NovelRT::Input
{
    void KeyStateFrameChangeLog::PushNewState(KeyState newState) noexcept
    {
        if (_currentState == newState)
        {
            return;
        }

        _currentState = newState;
        _changeCount++;
    }

    KeyState KeyStateFrameChangeLog::GetCurrentState() const noexcept
    {
        return _currentState;
    }

    uint32_t KeyStateFrameChangeLog::GetChangeCount() const noexcept
    {
        return _changeCount;
    }
}
