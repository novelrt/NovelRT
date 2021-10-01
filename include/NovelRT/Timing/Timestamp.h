// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_TIMING_DELTATIMESTAMP_H
#define NOVELRT_TIMING_DELTATIMESTAMP_H

#include <cassert>
#include <stdint.h>

namespace NovelRT::Timing
{
    // Windows and some other platforms use 100ns ticks
    static const uint64_t TicksPerSecond = 10'000'000;
    class Timestamp
    {
    public:
        uint64_t ticks;

        explicit Timestamp(uint64_t ticks) noexcept : ticks(ticks)
        {
        }

        inline double getSecondsDouble() const noexcept
        {
            auto returnVal = static_cast<double>(ticks) / TicksPerSecond;
            assert((returnVal != 0.0 || ticks == 0) &&
                   "Timestamp can't be represented in seconds as a double, tick value is too small!");
            return returnVal;
        }

        inline float getSecondsFloat() const noexcept
        {
            auto returnVal = static_cast<float>(getSecondsDouble());
            assert((returnVal != 0.0f || ticks == 0) &&
                   "Timestamp can't be represented in seconds as a float, tick value is too small!");
            return returnVal;
        }

        inline static const Timestamp zero() noexcept
        {
            return Timestamp(0ULL);
        }

        inline static const Timestamp fromSeconds(double seconds) noexcept
        {
            return Timestamp(static_cast<uint64_t>(seconds * TicksPerSecond));
        }

        inline Timestamp operator+(const Timestamp& other) const noexcept
        {
            return Timestamp(ticks + other.ticks);
        }

        inline Timestamp operator-(const Timestamp& other) const noexcept
        {
            return Timestamp(ticks - other.ticks);
        }

        inline Timestamp operator*(const Timestamp& other) const noexcept
        {
            return Timestamp(ticks * other.ticks);
        }

        inline Timestamp operator/(const Timestamp& other) const noexcept
        {
            return Timestamp(ticks / other.ticks);
        }

        inline Timestamp& operator+=(const Timestamp& other) noexcept
        {
            ticks += other.ticks;
            return *this;
        }

        inline Timestamp operator-=(const Timestamp& other) noexcept
        {
            ticks -= other.ticks;
            return *this;
        }

        inline Timestamp operator*=(const Timestamp& other) noexcept
        {
            ticks *= other.ticks;
            return *this;
        }

        inline Timestamp operator/=(const Timestamp& other) noexcept
        {
            ticks /= other.ticks;
            return *this;
        }

        inline bool operator<(const Timestamp& other) const noexcept
        {
            return ticks < other.ticks;
        }

        inline bool operator>(const Timestamp& other) const noexcept
        {
            return ticks > other.ticks;
        }

        inline bool operator<=(const Timestamp& other) const noexcept
        {
            return ticks <= other.ticks;
        }

        inline bool operator>=(const Timestamp& other) const noexcept
        {
            return ticks >= other.ticks;
        }

        inline bool operator==(const Timestamp& other) const noexcept
        {
            return ticks == other.ticks;
        }

        inline bool operator!=(const Timestamp& other) const noexcept
        {
            return ticks != other.ticks;
        }
    };
}

#endif //! NOVELRT_TIMING_DELTATIMESTAMP_H
