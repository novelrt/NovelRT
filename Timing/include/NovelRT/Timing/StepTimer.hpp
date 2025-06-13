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
        uint64_t _secondCounter;
        uint64_t _remainingTicks;

        uint64_t _elapsedTicks;
        uint64_t _totalTicks;

        uint32_t _frameCount;
        uint32_t _framesPerSecond;
        uint32_t _framesThisSecond;

        bool _isFixedTimeStep;

    public:
        StepTimer(uint32_t targetFrameRate = 0, double maxSecondDelta = 0.1) noexcept;

        inline uint64_t getElapsedTicks() const noexcept
        {
            return _elapsedTicks;
        }
        inline uint64_t getTotalTicks() const noexcept
        {
            return _totalTicks;
        }

        inline Timestamp getElapsedTime() const noexcept
        {
            auto elapsedTicks = getElapsedTicks();
            return TimeFromTicks(elapsedTicks);
        }
        inline Timestamp getTotalTime() const noexcept
        {
            auto totalTicks = getTotalTicks();
            return TimeFromTicks(totalTicks);
        }

        inline Timestamp::duration GetTargetElapsedTime() const noexcept
        {
            return _targetFrequency;
        }

        inline uint32_t getFrameCount() const noexcept
        {
            return _frameCount;
        }
        inline uint32_t getFramesPerSecond() const noexcept
        {
            return _framesPerSecond;
        }

        inline const bool& isFixedTimeStep() const noexcept
        {
            return _isFixedTimeStep;
        }

        inline bool& isFixedTimeStep() noexcept
        {
            return _isFixedTimeStep;
        }

        void resetElapsedTime() noexcept;
        void Tick(const Utilities::Event<Timestamp::duration>& update);
    };
}
