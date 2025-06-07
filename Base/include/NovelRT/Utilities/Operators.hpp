#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <type_traits>

template<class T, class U = std::underlying_type_t<T>>
constexpr T operator~(T a)
{
    return static_cast<T>(~static_cast<U>(a));
}

template<class T, class U = std::underlying_type_t<T>>
constexpr T operator|(T a, T b)
{
    return static_cast<T>((static_cast<U>(a) | static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>>
constexpr T operator&(T a, T b)
{
    return static_cast<T>((static_cast<U>(a) & static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>>
constexpr T operator^(T a, T b)
{
    return static_cast<T>((static_cast<U>(a) ^ static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>>
constexpr T& operator|=(T& a, T b)
{
    return a = static_cast<T>((static_cast<U>(a) | static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>>
constexpr T& operator&=(T& a, T b)
{
    return a = static_cast<T>((static_cast<U>(a) & static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>>
constexpr T& operator^=(T& a, T b)
{
    return a = static_cast<T>((static_cast<U>(a) ^ static_cast<U>(b)));
}
