module;

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

export module NovelRT.Maths:Constants;

namespace NovelRT::Maths
{
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
    export template <typename T>
    constexpr T Tau;

    export template <>
    constexpr float Tau<float> = 6.283185307f;

    export template <>
    constexpr double Tau<double> = 6.283185307179586476925;
}
