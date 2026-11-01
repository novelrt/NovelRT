#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// This is based on the StepTimer provided in the DirectX ToolKit
// Original code is available under the MIT Licence

#include <NovelRT/Timing/Timestamp.hpp>
#include <NovelRT/Utilities/Event.hpp>

namespace NovelRT::Timing
{
    class StepTimer
    {
    private:
        const GameClock::duration _maxCounterDelta;
        const GameClock::duration _targetFrequency;

        Timestamp _lastCounter;
        uint64_t _remainingTicks;

        uint64_t _totalTicks;

        bool _isFixedTimeStep;

    public:
        StepTimer(uint32_t targetFrameRate = 0, double maxSecondDelta = 0.1) noexcept;

        Timestamp::duration GetTargetFrequency() const noexcept
        {
            return _targetFrequency;
        }

        bool IsFixedTimeStep() const noexcept
        {
            return _isFixedTimeStep;
        }

        void Tick(const Utilities::Event<Timestamp, Timestamp::duration>& update);
    };
}
