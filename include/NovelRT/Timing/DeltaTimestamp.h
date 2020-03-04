// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_TIMING_DELTATIMESTAMP_H
#define NOVELRT_TIMING_DELTATIMESTAMP_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Timing {
  class DeltaTimestamp {
  private:
    const uint64_t _tickDelta;
    const double _doubleDelta;
    const float _floatDelta;
  public:
    DeltaTimestamp(uint64_t tickDelta, double doubleDelta, float floatDelta);

    inline uint64_t getTickDelta() {
      return _tickDelta;
    }

    inline double getDoubleDelta() {
      return _doubleDelta;
    }

    inline float getFloatDelta() {
      return _floatDelta;
    }

  };
}

#endif //!NOVELRT_TIMING_DELTATIMESTAMP_H
