// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_TIMING_DELTATIMESTAMP_H
#define NOVELRT_TIMING_DELTATIMESTAMP_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Timing {
  class Timestamp {
  private:
    const uint64_t _tickDelta;

  public:
    Timestamp(uint64_t ticks);

    inline uint64_t getTickDelta() const {
      return _tickDelta;
    }

    inline double getDoubleDelta() const {
      return static_cast<double>(_tickDelta) / TicksPerSecond;
    }

    inline float getFloatDelta() const {
      return static_cast<float>(_tickDelta) / TicksPerSecond;
    }

  };
}

#endif //!NOVELRT_TIMING_DELTATIMESTAMP_H
