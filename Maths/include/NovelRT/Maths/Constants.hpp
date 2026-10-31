#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Maths
{
    /**
     * @brief Retrieves a constant for a half rotation expressed in radians.
     *
     * @details
     * A half rotation is expressed as: \f[
     *      \pi = 3.14159265358979323846...
     * \f]
     * In this implementation it is expressed as \f(3.141592654f\f), or as \f(3.14159265358979323846\f).
     *
     * @tparam T A floating point type that is expressed as either float or double.
     * @return A half rotation expressed in radians.
     */
    template<typename T>
    constexpr inline T Pi;

    template<>
    constexpr inline float Pi<float> = 3.141592654f;

    template<>
    constexpr inline double Pi<double> = 3.14159265358979323846;

    /**
     * @brief Retrieves a constant for a full rotation expressed in radians.
     *
     * @details
     * A full rotation is expressed as: \f[
     *      2\pi = 6.283185307179586476925...
     * \f]
     * In this implementation it is expressed as \f(6.283185307f\f), or as \f(6.283185307179586476925\f).
     *
     * @tparam TFloatingPointType A floating point type that is expressed as either float or double.
     * @return A full rotation expressed in radians.
     */
    template<typename T>
    constexpr inline T Tau;

    template<>
    constexpr inline float Tau<float> = 6.283185307f;

    template<>
    constexpr inline double Tau<double> = 6.283185307179586476925;
}
