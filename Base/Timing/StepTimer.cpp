// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// This is based on the StepTimer provided in the DirectX ToolKit
// Original code is available under the MIT Licence

#include <NovelRT/Timing/StepTimer.hpp>

namespace NovelRT::Timing
{
    StepTimer::StepTimer(uint32_t targetFrameRate, double maxSecondDelta) noexcept
        :
          _maxCounterDelta(TimeFromSeconds(maxSecondDelta).time_since_epoch()),
          _targetFrequency(TimeFromFrequency<double>((targetFrameRate != 0) ? targetFrameRate : 60).time_since_epoch()), // 60fps, if nothing else specified
          _lastCounter(GameClock::now()),
          _secondCounter(0),
          _remainingTicks(0),
          _elapsedTicks(0),
          _totalTicks(0),
          _frameCount(0),
          _framesPerSecond(0),
          _framesThisSecond(0),
          _isFixedTimeStep(targetFrameRate != 0)
    {
    }

    void StepTimer::resetElapsedTime() noexcept
    {
        _lastCounter = GameClock::now();
        _secondCounter = 0;
        _remainingTicks = 0;
        _framesPerSecond = 0;
        _framesThisSecond = 0;
    }

    void StepTimer::Tick(const Utilities::Event<Timestamp::duration>& update)
    {
        auto currentCounter = GameClock::now();
        auto counterDelta = currentCounter - _lastCounter;

        // This handles excessibly large deltas to avoid overcompting.
        // It is particularly beneficial to do this when debugging, for example
        auto ticksDelta = std::min(counterDelta, _maxCounterDelta);

        if (ticksDelta.count() == 0)
            return;

        _lastCounter = currentCounter;
        _secondCounter += counterDelta.count();

        auto lastFrameCount = _frameCount;

        if (_isFixedTimeStep)
        {
            // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
            // the clock to exactly match the target value. This prevents tiny and irrelevant errors
            // from accumulating over time. Without this clamping, a game that requested a 60 fps
            // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
            // accumulate enough tiny errors that it would drop a frame. It is better to just round
            // small deviations down to zero to leave things running smoothly.

            using QuarterMillisecond = std::ratio_multiply<std::milli, std::ratio<1, 4>>;
            constexpr auto OneQuarterMillisecond = std::chrono::duration<int64_t, QuarterMillisecond>{1};

            using SignedDuration = std::chrono::duration<int64_t, GameClock::period>;
            auto delta = std::chrono::duration_cast<Timestamp::duration>(std::chrono::abs(std::chrono::duration_cast<SignedDuration>(ticksDelta) - std::chrono::duration_cast<SignedDuration>(_targetFrequency)));
            if (delta < OneQuarterMillisecond)
            {
                ticksDelta = _targetFrequency;
            }

            _remainingTicks += delta.count();

            while (_remainingTicks >= _targetFrequency.count())
            {
                _elapsedTicks = _targetFrequency.count();
                _totalTicks += _targetFrequency.count();
                _remainingTicks -= _targetFrequency.count();
                _frameCount++;

                update(ticksDelta);
            }
        }
        else
        {
            // variable timestep update logic

            _elapsedTicks = ticksDelta.count();
            _totalTicks += ticksDelta.count();
            _remainingTicks = 0;
            _frameCount++;

            update(ticksDelta);
        }

        // Track the current framerate
        if (_frameCount != lastFrameCount)
        {
            _framesThisSecond++;
        }

        if (_secondCounter >= _targetFrequency.count())
        {
            _framesPerSecond = _framesThisSecond;
            _framesThisSecond = 0;
            _secondCounter %= _targetFrequency.count();
        }
    }
} // namespace NovelRT::Timing
