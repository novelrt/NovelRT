// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// This is based on the StepTimer provided in the DirectX ToolKit
// Original code is available under the MIT Licence

#include "Timestamp.h"

#ifndef NOVELRT_TIMING_STEPTIMER_H
#define NOVELRT_TIMING_STEPTIMER_H

namespace NovelRT::Timing
{
    class StepTimer
    {
    private:
        const uint64_t _frequency;
        const uint64_t _maxCounterDelta;

        uint64_t _lastCounter;
        uint64_t _secondCounter;
        uint64_t _remainingTicks;

        uint64_t _elapsedTicks;
        uint64_t _totalTicks;
        uint64_t _targetElapsedTicks;

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
            return Timestamp(elapsedTicks);
        }
        inline Timestamp getTotalTime() const noexcept
        {
            auto totalTicks = getTotalTicks();
            return Timestamp(totalTicks);
        }

        inline const uint64_t& targetElapsedTicks() const noexcept
        {
            return _targetElapsedTicks;
        }

        inline uint64_t& targetElapsedTicks() noexcept
        {
            return _targetElapsedTicks;
        }

        inline Timestamp getTargetElapsedTime() const noexcept
        {
            auto ticks = targetElapsedTicks();
            return Timestamp(ticks);
        }
        inline void setTargetElapsedTime(Timestamp value) noexcept
        {
            targetElapsedTicks() = value.ticks;
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
        void tick(const Utilities::Event<Timestamp>& update);
    };
} // namespace NovelRT::Timing

#endif // NOVELRT_TIMING_STEPTIMER_H
