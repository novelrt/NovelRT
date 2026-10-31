#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cmath>

#include <NovelRT/Maths/Constants.hpp>

/**
 * @brief Contains stateless policies that control the rate of progress through an animation.
 *
 * @details Each policy accepts normalised elapsed time \f$t \in [0, 1]\f$ and returns adjusted progress.
 * The built-in curves map zero to zero and one to one, and remain within this interval. They do not clamp
 * their arguments. Interpolation converts the adjusted progress into a component member value separately.
 * In policies start slowly, Out policies finish slowly, and InOut policies do both.
 */
namespace NovelRT::Ecs::Animation::Easing
{
    namespace Detail
    {
        /**
         * @brief Constructs an ease-out curve by reflecting an ease-in curve.
         *
         * @details Given an ease-in curve \f$f\f$, the resulting curve is:
         * \f[
         *     g(t) = 1 - f(1 - t).
         * \f]
         *
         * @tparam TIn A default-constructible policy callable on a const instance with a float progress value.
         * Its call operator must return a float-compatible value without throwing.
         */
        template<typename TIn>
        struct Out
        {
            /**
             * @brief Evaluates the reflected ease-in curve.
             * @param progress The normalised elapsed time in the interval [0, 1].
             * @return The adjusted ease-out progress.
             */
            [[nodiscard]] constexpr float operator()(float progress) const noexcept
            {
                return 1.0f - TIn{}(1.0f - progress);
            }
        };

        /**
         * @brief Fits an ease-in curve into the first half and its ease-out counterpart into the second half.
         *
         * @details Given an ease-in curve \f$f\f$, the resulting curve is:
         * \f[
         *     g(t) = \begin{cases}
         *         \frac{1}{2} f(2t), & t < \frac{1}{2}, \\
         *         1 - \frac{1}{2} f(2 - 2t), & t \geq \frac{1}{2}.
         *     \end{cases}
         * \f]
         *
         * @tparam TIn A default-constructible policy callable on a const instance with a float progress value.
         * Its call operator must return a float-compatible value without throwing.
         */
        template<typename TIn>
        struct InOut
        {
            /**
             * @brief Evaluates the ease-in or ease-out half of the curve.
             * @param progress The normalised elapsed time in the interval [0, 1].
             * @return The adjusted ease-in-out progress.
             */
            [[nodiscard]] constexpr float operator()(float progress) const noexcept
            {
                if (progress < 0.5f)
                {
                    return 0.5f * TIn{}(progress * 2.0f);
                }

                return 0.5f + (0.5f * Out<TIn>{}((progress * 2.0f) - 1.0f));
            }
        };
    }

    /**
     * @brief Preserves progress to produce a constant rate through the interpolation.
     * @details \f[f(t) = t.\f]
     */
    struct Linear
    {
        /**
         * @brief Returns the supplied progress unchanged.
         * @param progress The normalised elapsed time in the interval [0, 1].
         * @return The unchanged progress.
         */
        [[nodiscard]] constexpr float operator()(float progress) const noexcept
        {
            return progress;
        }
    };

    /**
     * @brief Starts slowly and accelerates using a quadratic curve.
     * @details \f[f(t) = t^2.\f]
     */
    struct InQuadratic
    {
        /**
         * @brief Evaluates quadratic ease-in progress.
         * @param progress The normalised elapsed time in the interval [0, 1].
         * @return The square of the supplied progress.
         */
        [[nodiscard]] constexpr float operator()(float progress) const noexcept
        {
            return progress * progress;
        }
    };

    /**
     * @brief Starts slowly and accelerates using a cubic curve.
     * @details \f[f(t) = t^3.\f]
     */
    struct InCubic
    {
        /**
         * @brief Evaluates cubic ease-in progress.
         * @param progress The normalised elapsed time in the interval [0, 1].
         * @return The cube of the supplied progress.
         */
        [[nodiscard]] constexpr float operator()(float progress) const noexcept
        {
            return progress * progress * progress;
        }
    };

    /**
     * @brief Starts slowly and accelerates using a sinusoidal curve.
     * @details \f[f(t) = 1 - \cos\left(\frac{\pi t}{2}\right).\f]
     */
    struct InSine
    {
        /**
         * @brief Evaluates sinusoidal ease-in progress.
         * @param progress The normalised elapsed time in the interval [0, 1].
         * @return The adjusted sinusoidal progress.
         * @note Constant evaluation is not required to be supported for this policy under C++20.
         */
        [[nodiscard]] float operator()(float progress) const noexcept
        {
            constexpr float halfPi = Maths::Pi<float> * 0.5f;
            return 1.0f - std::cos(progress * halfPi);
        }
    };

    /**
     * @brief Finishes slowly using a quadratic curve.
     * @details \f[f(t) = 1 - (1 - t)^2.\f]
     * @see InQuadratic
     */
    using OutQuadratic = Detail::Out<InQuadratic>;
    /**
     * @brief Starts and finishes slowly using a quadratic curve.
     * @details
     * \f[
     *     f(t) = \begin{cases}
     *         2t^2, & t < \frac{1}{2}, \\
     *         1 - 2(1 - t)^2, & t \geq \frac{1}{2}.
     *     \end{cases}
     * \f]
     * @see InQuadratic
     */
    using InOutQuadratic = Detail::InOut<InQuadratic>;

    /**
     * @brief Finishes slowly using a cubic curve.
     * @details \f[f(t) = 1 - (1 - t)^3.\f]
     * @see InCubic
     */
    using OutCubic = Detail::Out<InCubic>;
    /**
     * @brief Starts and finishes slowly using a cubic curve.
     * @details
     * \f[
     *     f(t) = \begin{cases}
     *         4t^3, & t < \frac{1}{2}, \\
     *         1 - 4(1 - t)^3, & t \geq \frac{1}{2}.
     *     \end{cases}
     * \f]
     * @see InCubic
     */
    using InOutCubic = Detail::InOut<InCubic>;

    /**
     * @brief Finishes slowly using a sinusoidal curve.
     * @details \f[f(t) = \sin\left(\frac{\pi t}{2}\right).\f]
     * @see InSine
     */
    using OutSine = Detail::Out<InSine>;
    /**
     * @brief Starts and finishes slowly using a sinusoidal curve.
     * @details \f[f(t) = \frac{1 - \cos(\pi t)}{2}.\f]
     * @see InSine
     */
    using InOutSine = Detail::InOut<InSine>;
}
