// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

// This is based on the StepTimer provided in the DirectX ToolKit
// Original code is available under the MIT Licence

#ifndef NOVELRT_STEPTIMER_H
#define NOVELRT_STEPTIMER_H

#include <stdint.h>
#include <vector>

namespace NovelRT {
  typedef void (*NovelUpdateSubscriber)(double deltaSeconds);

  class StepTimer {
  public:
    // Windows and some other platforms use 100ns ticks
    static const uint64_t TicksPerSecond = 10'000'000;

    StepTimer(uint32_t targetFrameRate = 0, double maxSecondDelta = 0.1);

    uint64_t getElapsedTicks() const;
    uint64_t getTotalTicks() const;

    double getElapsedSeconds() const;
    double getTotalSeconds() const;

    uint64_t getTargetElapsedTicks() const;
    void setTargetElapsedTicks(uint64_t value);

    double getTargetElapsedSeconds() const;
    void setTargetElapsedSeconds(double value);

    uint32_t getFrameCount() const;
    uint32_t getFramesPerSecond() const;

    bool getIsFixedTimeStep() const;
    void setIsFixedTimeStep(bool value);

    static double TicksToSeconds(uint64_t ticks) {
      return (double)ticks / TicksPerSecond;
    }

    static uint64_t SecondsToTicks(double seconds) {
      return (uint64_t)(seconds * TicksPerSecond);
    }

    void resetElapsedTime();
    void tick(const std::vector<NovelUpdateSubscriber>& update);

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
  };

  inline uint64_t StepTimer::getElapsedTicks() const {
    return _elapsedTicks;
  }

  inline uint64_t StepTimer::getTotalTicks() const {
    return _totalTicks;
  }

  inline double StepTimer::getElapsedSeconds() const {
    auto elapsedTicks = getElapsedTicks();
    return TicksToSeconds(elapsedTicks);
  }

  inline double StepTimer::getTotalSeconds() const {
    auto totalTicks = getTotalTicks();
    return TicksToSeconds(totalTicks);
  }

  inline uint32_t StepTimer::getFrameCount() const {
    return _frameCount;
  }

  inline uint32_t StepTimer::getFramesPerSecond() const {
    return _framesPerSecond;
  }

  inline bool StepTimer::getIsFixedTimeStep() const {
    return _isFixedTimeStep;
  }

  inline void StepTimer::setIsFixedTimeStep(bool value) {
    _isFixedTimeStep = value;
  }

  inline uint64_t StepTimer::getTargetElapsedTicks() const {
    return _targetElapsedTicks;

  }

  inline void StepTimer::setTargetElapsedTicks(uint64_t value) {
    _targetElapsedTicks = value;
  }

  inline double StepTimer::getTargetElapsedSeconds() const {
    auto targetElapsedTicks = getTargetElapsedTicks();
    return TicksToSeconds(targetElapsedTicks);
  }

  inline void StepTimer::setTargetElapsedSeconds(double value) {
    auto targetElapsedTicks = SecondsToTicks(value);
    setTargetElapsedTicks(targetElapsedTicks);
  }
}
#endif // NOVELRT_STEPTIMER_H
