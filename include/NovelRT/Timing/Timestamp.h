// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_TIMING_DELTATIMESTAMP_H
#define NOVELRT_TIMING_DELTATIMESTAMP_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Timing {
  class Timestamp {
  private:
    const uint64_t _ticks;

  public:
    Timestamp::Timestamp(uint64_t ticks) : _ticks(ticks) {}

    inline uint64_t getTicks() const {
      return _ticks;
    }

    inline double getSecondsDouble() const {
      return static_cast<double>(_ticks) / TicksPerSecond;
    }

    inline float getSecondsFloat() const {
      return static_cast<float>(_ticks) / TicksPerSecond;
    }

  };
}

#endif //!NOVELRT_TIMING_DELTATIMESTAMP_H
