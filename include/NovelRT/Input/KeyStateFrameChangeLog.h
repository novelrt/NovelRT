// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_KEYSTATEFRAMECHANGELOG_H
#define NOVELRT_INPUT_KEYSTATEFRAMECHANGELOG_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input
{
    class KeyStateFrameChangeLog
    {
        friend class InteractionService;

    private:
        KeyState _currentState = KeyState::Idle;
        uint32_t _changeCount = 0;

        inline void pushNewState(KeyState newState) noexcept
        {
            if (_currentState == newState)
            {
                return;
            }

            _currentState = newState;
            _changeCount++;
        }

    public:
        inline KeyState getCurrentState() const noexcept
        {
            return _currentState;
        }

        inline uint32_t getChangeCount() const noexcept
        {
            return _changeCount;
        }
    };

    inline bool operator==(const KeyStateFrameChangeLog& lhs, const KeyState& rhs) noexcept
    {
        return lhs.getCurrentState() == rhs;
    }

    inline bool operator==(const KeyState& lhs, const KeyStateFrameChangeLog& rhs) noexcept
    {
        return rhs == lhs;
    }
}
#endif //! NOVELRT_INPUT_KEYSTATEFRAMECHANGELOG_H
