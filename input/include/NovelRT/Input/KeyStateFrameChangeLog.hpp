// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_KEYSTATEFRAMECHANGELOG_H
#define NOVELRT_INPUT_KEYSTATEFRAMECHANGELOG_H

#ifndef NOVELRT_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Input
{
    class KeyStateFrameChangeLog
    {

    private:
        KeyState _currentState = KeyState::Idle;
        uint32_t _changeCount = 0;

    public:
        inline void PushNewState(KeyState newState) noexcept
        {
            if (_currentState == newState)
            {
                return;
            }

            _currentState = newState;
            _changeCount++;
        }

        inline KeyState GetCurrentState() const noexcept
        {
            return _currentState;
        }

        inline uint32_t GetChangeCount() const noexcept
        {
            return _changeCount;
        }
    };

    inline bool operator==(const KeyStateFrameChangeLog& lhs, const KeyState& rhs) noexcept
    {
        return lhs.GetCurrentState() == rhs;
    }

    inline bool operator==(const KeyState& lhs, const KeyStateFrameChangeLog& rhs) noexcept
    {
        return rhs == lhs;
    }
}
#endif //! NOVELRT_INPUT_KEYSTATEFRAMECHANGELOG_H
