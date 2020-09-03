// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_TIMING_DELTATIMESTAMP_H
#define NOVELRT_TIMING_DELTATIMESTAMP_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Timing {
  class Timestamp {
  public:
    uint64_t _ticks;

    explicit Timestamp(uint64_t ticks) noexcept : _ticks(ticks) {}

    inline double getSecondsDouble() const {
      auto returnVal = static_cast<double>(_ticks) / TicksPerSecond;
      assert((returnVal != 0.0 || _ticks == 0) && "Timestamp can't be represented in seconds as a double, tick value is too small!");
      return returnVal;
    }

    inline float getSecondsFloat() const {
      auto returnVal = static_cast<float>(getSecondsDouble());
      assert((returnVal != 0.0f || _ticks == 0) && "Timestamp can't be represented in seconds as a float, tick value is too small!");
      return returnVal;
    }

    inline static const Timestamp zero() {
      return Timestamp(0ULL);
    }

    inline static const Timestamp fromSeconds(double seconds) {
      return Timestamp(static_cast<uint64_t>(seconds * TicksPerSecond));
    }

    inline Timestamp operator+(const Timestamp& other) const {
      return Timestamp(_ticks + other._ticks);
    }

    inline Timestamp operator-(const Timestamp& other) const {
      return Timestamp(_ticks - other._ticks);
    }

    inline Timestamp operator*(const Timestamp& other) const {
      return Timestamp(_ticks * other._ticks);
    }

    inline Timestamp operator/(const Timestamp& other) const {
      return Timestamp(_ticks / other._ticks);
    }

    inline Timestamp& operator+=(const Timestamp& other) {
      _ticks += other._ticks;
      return *this;
    }

    inline Timestamp operator-=(const Timestamp& other) {
      _ticks -= other._ticks;
      return *this;
    }

    inline Timestamp operator*=(const Timestamp& other) {
      _ticks *= other._ticks;
      return *this;
    }

    inline Timestamp operator/=(const Timestamp& other) {
      _ticks /= other._ticks;
      return *this;
    }

    inline bool operator<(const Timestamp& other) const {
      return _ticks < other._ticks;
    }

    inline bool operator>(const Timestamp& other) const {
      return _ticks > other._ticks;
    }

    inline bool operator<=(const Timestamp& other) const {
      return _ticks <= other._ticks;
    }

    inline bool operator>=(const Timestamp& other) const {
      return _ticks >= other._ticks;
    }

    inline bool operator==(const Timestamp& other) const {
      return _ticks == other._ticks;
    }

    inline bool operator!=(const Timestamp& other) const {
      return _ticks != other._ticks;
    }
  };
}

#endif //!NOVELRT_TIMING_DELTATIMESTAMP_H
