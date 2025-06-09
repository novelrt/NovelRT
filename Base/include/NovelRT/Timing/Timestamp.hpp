#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <chrono>
#include <cstdint>
#include <type_traits>

namespace NovelRT::Timing
{
    struct GameClock
    {
        // NOLINTBEGIN - stdlib compatibility
        using rep = uint64_t;
        using period = std::ratio_multiply<std::hecto, std::nano>;
        using duration = std::chrono::duration<rep, period>;
        using time_point = std::chrono::time_point<GameClock>;

        const bool is_steady = false;

        static time_point now() noexcept;
        // NOLINTEND
    };

    using Timestamp = GameClock::time_point;

    template<typename Rep, typename Period>
    constexpr Timestamp TimeFrom(const std::chrono::duration<Rep, Period>& value) noexcept
    {
        return Timestamp{std::chrono::duration_cast<GameClock::duration>(value)};
    }

    constexpr Timestamp TimeFromTicks(uint64_t value) noexcept
    {
        return TimeFrom(GameClock::duration{value});
    }

    template<typename T>
    constexpr Timestamp TimeFromSeconds(T seconds) noexcept
    {
        return TimeFrom(std::chrono::duration<T>(seconds));
    }

    template<typename T>
    constexpr Timestamp TimeFromFrequency(T frequency) noexcept
    {
        static_assert(std::is_floating_point_v<T>, "T must be able to represent values between 0 and 1");

        return TimeFrom(std::chrono::duration<T>(1) / frequency);
    }

    template<typename T>
    constexpr T GetSeconds(const Timestamp& timestamp) noexcept
    {
        return std::chrono::duration_cast<std::chrono::duration<T>>(timestamp.time_since_epoch()).count();
    }

    template<typename T>
    constexpr T GetSeconds(const GameClock::duration& duration) noexcept
    {
        return std::chrono::duration_cast<std::chrono::duration<T>>(duration).count();
    }
}
