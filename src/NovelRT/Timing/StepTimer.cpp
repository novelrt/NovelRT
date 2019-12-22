// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

// This is based on the StepTimer provided in the DirectX ToolKit
// Original code is available under the MIT Licence

#include <NovelRT.h>
#include <SDL2/SDL.h>

namespace NovelRT::Timing {
  StepTimer::StepTimer(uint32_t targetFrameRate, double maxSecondDelta) :
    _frequency(SDL_GetPerformanceFrequency()),
    _maxCounterDelta((uint64_t)(_frequency * maxSecondDelta)),
    _lastCounter(SDL_GetPerformanceCounter()),
    _secondCounter(0),
    _remainingTicks(0),
    _elapsedTicks(0),
    _totalTicks(0),
    _targetElapsedTicks(TicksPerSecond / ((targetFrameRate != 0) ? targetFrameRate : 60)), // 60fps, if nothing else specified
    _frameCount(0),
    _framesPerSecond(0),
    _framesThisSecond(0),
    _isFixedTimeStep(targetFrameRate != 0) {
  }

  void StepTimer::resetElapsedTime() {
    _lastCounter = SDL_GetPerformanceCounter();
    _secondCounter = 0;
    _remainingTicks = 0;
    _framesPerSecond = 0;
    _framesThisSecond = 0;
  }

  void StepTimer::tick(const std::vector<NovelUpdateSubscriber>& update) {

    auto currentCounter = SDL_GetPerformanceCounter();
    auto counterDelta = currentCounter - _lastCounter;

    _lastCounter = currentCounter;
    _secondCounter += counterDelta;

    if (counterDelta > _maxCounterDelta)
    {
      // This handles excessibly large deltas to avoid overcompting.
      // It is particularly beneficial to do this when debugging, for example
      counterDelta = _maxCounterDelta;
    }

    // Convert to the "canonicalized" tick format of TicksPerSecond
    // This will never overflow due to the clamping we did above
    auto ticksDelta = (counterDelta * TicksPerSecond) / _frequency;

    auto lastFrameCount = _frameCount;

    if (_isFixedTimeStep) {
      // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
      // the clock to exactly match the target value. This prevents tiny and irrelevant errors
      // from accumulating over time. Without this clamping, a game that requested a 60 fps
      // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
      // accumulate enough tiny errors that it would drop a frame. It is better to just round
      // small deviations down to zero to leave things running smoothly.

      auto targetElapsedTicks = _targetElapsedTicks;

      if (abs((int64_t)(ticksDelta - targetElapsedTicks)) < (int64_t)(TicksPerSecond / 4000)) {
        ticksDelta = targetElapsedTicks;
      }

      _remainingTicks += ticksDelta;

      auto secondsDelta = TicksToSeconds(targetElapsedTicks);

      while (_remainingTicks >= targetElapsedTicks) {
        _elapsedTicks = targetElapsedTicks;
        _totalTicks += targetElapsedTicks;
        _remainingTicks -= targetElapsedTicks;
        _frameCount++;

        for (auto subscriber : update) {
          subscriber(secondsDelta);
        }
      }
    } else {
      // variable timestep update logic

      _elapsedTicks = ticksDelta;
      _totalTicks += ticksDelta;
      _remainingTicks = 0;
      _frameCount++;

      auto secondsDelta = TicksToSeconds(ticksDelta);

      for (auto subscriber : update) {
        subscriber(secondsDelta);
      }
    }

    // Track the current framerate
    if (_frameCount != lastFrameCount) {
      _framesThisSecond++;
    }

    if (_secondCounter >= _frequency) {
      _framesPerSecond = _framesThisSecond;
      _framesThisSecond = 0;
      _secondCounter %= _frequency;
    }
  }
}
