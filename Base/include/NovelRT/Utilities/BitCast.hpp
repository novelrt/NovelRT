#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifdef __has_builtin
#define NOVELRT_UTILITIES_HAS_BUILTIN_BIT_CAST __has_builtin(__builtin_bit_cast)
#else
#define NOVELRT_UTILITIES_HAS_BUILTIN_BIT_CAST false
#endif

#if __has_include(<version>)
#include <version>
#endif

#if __cpp_lib_bit_cast
#include <bit>
#endif

#include <type_traits>

namespace NovelRT::Utilities
{
    /**
     * @brief Casts an object instance as an unrelated object of a different type.
     *
     * @details
     * With this implementation types can only be casted to other types that are of equal size and that are
     * trivially copyable.
     *
     * @tparam TTo The target type the instance should be casted to.
     * @tparam TFrom The original type of the object instance.
     * @returns The object instance as a TTo.
     */
    template<class TTo, class TFrom>
#if __cpp_lib_bit_cast
    constexpr static std::enable_if_t<sizeof(TTo) == sizeof(TFrom) && std::is_trivially_copyable_v<TTo> &&
                                            std::is_trivially_copyable_v<TFrom>,
                                        TTo>
    BitCast(const TFrom& value) noexcept
    {
        return std::bit_cast<TTo>(value);
    }
#elif NOVELRT_UTILITIES_HAS_BUILTIN_BIT_CAST
    constexpr static std::enable_if_t<sizeof(TTo) == sizeof(TFrom) && std::is_trivially_copyable_v<TTo> &&
                                            std::is_trivially_copyable_v<TFrom>,
                                        TTo>
    BitCast(const TFrom& value) noexcept
    {
        return __builtin_bit_cast(TTo, value);
    }
#else
    inline static std::enable_if_t<sizeof(TTo) == sizeof(TFrom) && std::is_trivially_copyable_v<TTo> &&
                                        std::is_trivially_copyable_v<TFrom>,
                                    TTo>
    BitCast(const TFrom& value) noexcept
    {
        return *reinterpret_cast<const TTo*>(&value);
    }
#endif
}
