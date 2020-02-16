// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

// This is based on the StepTimer provided in the DirectX ToolKit
// Original code is available under the MIT Licence

#ifndef NOVELRT_TIMING_STEPTIMER_H
#define NOVELRT_TIMING_STEPTIMER_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Timing {
  class StepTimer {
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
    // Windows and some other platforms use 100ns ticks
    static const uint64_t TicksPerSecond = 10'000'000;

    StepTimer(uint32_t targetFrameRate = 0, double maxSecondDelta = 0.1);

    inline uint64_t getElapsedTicks() const {
      return _elapsedTicks;
    }
    inline uint64_t getTotalTicks() const {
      return _totalTicks;
    }

    inline double getElapsedSeconds() const {
      auto elapsedTicks = getElapsedTicks();
      return TicksToSeconds(elapsedTicks);
    }
    inline double getTotalSeconds() const {
      auto totalTicks = getTotalTicks();
      return TicksToSeconds(totalTicks);
    }

    inline uint64_t getTargetElapsedTicks() const {
      return _targetElapsedTicks;
    }
    inline void setTargetElapsedTicks(uint64_t value) {
      _targetElapsedTicks = value;
    }

    inline double getTargetElapsedSeconds() const {
      auto targetElapsedTicks = getTargetElapsedTicks();
      return TicksToSeconds(targetElapsedTicks);
    }
    inline void setTargetElapsedSeconds(double value) {
      auto targetElapsedTicks = SecondsToTicks(value);
      setTargetElapsedTicks(targetElapsedTicks);
    }

    inline uint32_t getFrameCount() const {
      return _frameCount;
    }
    inline uint32_t getFramesPerSecond() const {
      return _framesPerSecond;
    }

    inline bool getIsFixedTimeStep() const {
      return _isFixedTimeStep;
    }
    inline void setIsFixedTimeStep(bool value) {
      _isFixedTimeStep = value;
    }

    static double TicksToSeconds(uint64_t ticks) {
      return (double)ticks / TicksPerSecond;
    }

    static uint64_t SecondsToTicks(double seconds) {
      return (uint64_t)(seconds * TicksPerSecond);
    }

    void resetElapsedTime();
    void tick(const std::vector<std::function<void(double)>>& update);
  };
}

#endif // NOVELRT_TIMING_STEPTIMER_H
