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

    StepTimer(uint32_t targetFrameRate = 0, double maxSecondDelta = 0.1);

    inline uint64_t getElapsedTicks() const {
      return _elapsedTicks;
    }
    inline uint64_t getTotalTicks() const {
      return _totalTicks;
    }

    inline Timestamp getElapsedTime() const {
      auto elapsedTicks = getElapsedTicks();
      return Timestamp(elapsedTicks);
    }
    inline Timestamp getTotalTime() const {
      auto totalTicks = getTotalTicks();
      return Timestamp(totalTicks);
    }

    inline const uint64_t& targetElapsedTicks() const {
      return _targetElapsedTicks;
    }

    inline uint64_t& targetElapsedTicks() {
      return _targetElapsedTicks;
    }

    inline Timestamp getTargetElapsedTime() const {
      auto ticks = targetElapsedTicks();
      return Timestamp(ticks);
    }
    inline void setTargetElapsedTime(Timestamp value) {
      targetElapsedTicks() = value._ticks;
    }

    inline uint32_t getFrameCount() const {
      return _frameCount;
    }
    inline uint32_t getFramesPerSecond() const {
      return _framesPerSecond;
    }

    inline const bool& isFixedTimeStep() const {
      return _isFixedTimeStep;
    }

    inline bool& isFixedTimeStep() {
      return _isFixedTimeStep;
    }

    void resetElapsedTime();
    void tick(const Utilities::Event<Timestamp>& update);
  };
}

#endif // NOVELRT_TIMING_STEPTIMER_H
