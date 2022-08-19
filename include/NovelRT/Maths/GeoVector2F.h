// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR2_H
#define NOVELRT_MATHS_GEOVECTOR2_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief Represents a vector with two components.
     */
    class GeoVector2F
    {
        friend class GeoVector3F;
        friend class GeoVector4F;

    private:
        explicit GeoVector2F(glm::vec2 value) noexcept : x(value.x), y(value.y)
        {
        }

    public:
        /**
         * @brief The X component of the vector.
         */
        float x;
        /**
         * @brief The Y component of the vector.
         */
        float y;

        /**
         * @brief Creates a GeoVector2F with all components set to zero.
         *
         * @return A GeoVector2F with all components set to zero.
         */
        GeoVector2F() noexcept : x(0.0f), y(0.0f)
        {
        }

        /**
         * @brief Creates a GeoVector2F with the given components.
         *
         * @param x The X component of the vector.
         * @param y The Y component of the vector.
         * @return A GeoVector2F with the given components.
         */
        GeoVector2F(float x, float y) noexcept : x(x), y(y)
        {
        }

        /**
         * @brief Constructs a unit GeoVector2F with a magnitude of one by normalising this vector.
         *
         * @details
         * To calculate a vector's unit vector you first calculate its magnitude and then divide the vector by its
         * magnitude \f[
         *      \vec{v}= \begin{pmatrix}
         *      4\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| = \sqrt{v_{x}^{2} + v_{y}^{2}} = \sqrt{4^{2} + 3^{2}} \rightarrow \sqrt{16 +
         *      9} = \sqrt{25} = 5\\
         *      \hat{v}=\frac{\vec{v}}{\left \| \vec{v} \right \|} =\frac{\bigl(\begin{smallmatrix}
         *      4\\
         *      3
         *      \end{smallmatrix}\bigr)}{5} = \begin{pmatrix}
         *      \tfrac{4}{5}\\
         *      \tfrac{3}{5}
         *      \end{pmatrix}\\
         *      \left \| \hat{v} \right \| = \sqrt{\tfrac{4}{5}^{2} + \tfrac{3}{5}^{2}} = \sqrt{\tfrac{16}{25} +
         *      \tfrac{9}{25}} \rightarrow \sqrt{\tfrac{25}{25}} \rightarrow \sqrt{1} = 1
         * \f]
         *
         * @return A unit GeoVector2F created from normalising this GeoVector2F.
         */
        inline GeoVector2F getNormalised() const noexcept
        {
            return GeoVector2F(glm::normalize(*reinterpret_cast<const glm::vec2*>(this)));
        }

        /**
         * @brief Calculates the magnitude of this GeoVector2F using its components. This is the same as the
         * calculating the vector's length.
         *
         * @details
         * To find a vector's magnitude you can use the Pythagorean theorem:\f[
         *      \vec{v}= \begin{pmatrix}
         *      4\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| = \sqrt{v_{x}^{2} + v_{y}^{2}} = \sqrt{4^{2} + 3^{2}} \rightarrow \sqrt{16 +
         *      9} = \sqrt{25} = 5
         * \f]
         *
         * @return The magnitude of this GeoVector2F.
         */
        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec2*>(this));
        }

        /**
         * @brief Calculates the length of this GeoVector2F using its components. This is the same as calculating the
         * vector's magnitude.
         *
         * @details
         * To find a vector's length you can use the Pythagorean theorem:\f[
         *      \vec{v}= \begin{pmatrix}
         *      4\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| = \sqrt{v_{x}^{2} + v_{y}^{2}} = \sqrt{4^{2} + 3^{2}} \rightarrow \sqrt{16 +
         *      9} = \sqrt{25} = 5
         * \f]
         *
         * @return The length of this GeoVector2F.
         */
        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if all components match.
         *
         * @param other The GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @returns true if all components matched, otherwise false.
         */
        inline bool operator==(GeoVector2F other) const noexcept
        {
            return *reinterpret_cast<const glm::vec2*>(this) == *reinterpret_cast<const glm::vec2*>(&other);
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if all components do not match.
         *
         * @param other The GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @returns true if any of the components do not match, otherwise false.
         */
        inline bool operator!=(GeoVector2F other) const noexcept
        {
            return *reinterpret_cast<const glm::vec2*>(this) != *reinterpret_cast<const glm::vec2*>(&other);
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if any of its components is less
         * than the other's components.
         *
         * @param other The GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @return true if any of the components is less than the other GeoVector2F's components, otherwise false.
         */
        inline bool operator<(GeoVector2F other) const noexcept
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec2*>(this), *reinterpret_cast<const glm::vec2*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if any of its components is less
         * than or equal to the other's components.
         *
         * @param other The GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @return true if any of the components is less than or equal to the other GeoVector2F's components,
         * otherwise false.
         */
        inline bool operator<=(GeoVector2F other) const noexcept
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec2*>(this),
                                               *reinterpret_cast<const glm::vec2*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if any of its components is greater
         * than the other's components.
         *
         * @param other The GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @return true if any of the components is greater than the other GeoVector2F's components, otherwise false.
         */
        inline bool operator>(GeoVector2F other) const noexcept
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec2*>(this),
                                             *reinterpret_cast<const glm::vec2*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if any of its components is greater
         * than or equal to the other's components.
         *
         * @param other The GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @return true if any of the components is greater than or equal to the other GeoVector2F's components,
         * otherwise false.
         */
        inline bool operator>=(GeoVector2F other) const noexcept
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec2*>(this),
                                                  *reinterpret_cast<const glm::vec2*>(&other)));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector2F and another GeoVector2F.
         *
         * @details
         * An example of an entrywise addition using two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      4\\
         *      5
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 + 4\\
         *      3 + 5
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      6\\
         *      8
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get added together with this vector.
         * @return A GeoVector2F where the components consist of the entrywise sum of this GeoVector2F and another
         * GeoVector2F.
         */
        inline GeoVector2F operator+(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) + *reinterpret_cast<const glm::vec2*>(&other));
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector2F and another GeoVector2F.
         *
         * @details
         * An example of an entrywise subtraction using two-dimensional dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      4\\
         *      7
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 - 4\\
         *      3 - 7
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      -2\\
         *      -4
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get subtracted from this vector.
         * @return A GeoVector2F where the components consist of the entrywise difference of this GeoVector2F and
         * another GeoVector2F.
         */
        inline GeoVector2F operator-(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) - *reinterpret_cast<const glm::vec2*>(&other));
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector2F and another GeoVector2F.
         *
         * @details
         * An example of a Hadamard product of two two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      5
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 * 4\\
         *      3 * 5
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      15
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get multiplied by this vector's components.
         * @return A GeoVector2F where the components consist of the Hadamard product of this GeoVector2F and another
         * GeoVector2F.
         */
        inline GeoVector2F operator*(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) * *reinterpret_cast<const glm::vec2*>(&other));
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector2F and another GeoVector2F.
         *
         * @details
         * An example of a Hadamard division of two two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{8}{2}\\
         *      \tfrac{6}{3}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      2
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose component act as a divisor for this vector's components.
         * @return A GeoVector2F where the components consist of the entrywise quotient of this GeoVector2F and another
         * GeoVector2F.
         */
        GeoVector2F operator/(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) / *reinterpret_cast<const glm::vec2*>(&other));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector2F and the provided scalar.
         *
         * @details
         * An example of summing up a two-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      +
         *      6
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      6\\
         *      6
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 + 6 \\
         *      6 + 6
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      14\\
         *      12
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets added up with each component of this vector.
         * @return A GeoVector2F where the components consist of the entrywise sum of this GeoVector2F and the provided
         * scalar.
         */
        inline GeoVector2F operator+(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) + other);
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector2F and the provided scalar.
         *
         * @details
         * An example of subtracting a scalar from a two-dimensional vector: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      -
         *      3
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      3\\
         *      3
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 - 3 \\
         *      6 - 3
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      5\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets subtracted from each component of this vector.
         * @return A GeoVector2F where the components consist of the entrywise difference of this GeoVector2F and the
         * provided scalar.
         */
        inline GeoVector2F operator-(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) - other);
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector2F and the provided scalar.
         *
         * @details
         * An example of a multiplication between a two-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      *
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 * 4 \\
         *      6 * 4
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      32\\
         *      24
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar who get multiplied by this vector's components.
         * @return A GeoVector2F where the components consist of the Hadamard product of this GeoVector2F and the
         * provided scalar.
         */
        inline GeoVector2F operator*(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) * other);
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector2F and the provided scalar.
         *
         * @details
         * An example of a division between a two-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      16\\
         *      12
         *      \end{pmatrix}
         *      /
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      16\\
         *      12
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{16}{4} \\
         *      \tfrac{12}{4}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that acts as the divisor for each component of this vector.
         * @return A GeoVector2F where the components consist of the entrywise quotient of this GeoVector2F and the
         * provided scalar.
         */
        GeoVector2F operator/(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) / other);
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector2F and another GeoVector2F and overwrites this instance
         * with the result.
         *
         * @details
         * An example of an entrywise addition using two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      4\\
         *      5
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 + 4\\
         *      3 + 5
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      6\\
         *      8
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get added together with this vector.
         * @return This GeoVector2F where the components consist of the entrywise sum of this GeoVector2F and another
         * GeoVector2F.
         */
        inline GeoVector2F& operator+=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) + *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector2F and another GeoVector2F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of an entrywise subtraction using two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      4\\
         *      7
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 - 4\\
         *      3 - 7
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      -2\\
         *      -4
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get subtracted from this vector.
         * @return This GeoVector2F where components consist of the entrywise difference of this GeoVector2F and another
         * GeoVector2F.
         */
        inline GeoVector2F& operator-=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) - *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector2F and another GeoVector2F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a Hadamard product of two two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      5
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 * 4\\
         *      3 * 5
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      15
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get multiplied by this vector's components.
         * @return This GeoVector2F where the components consist of the Hadamard product of this GeoVector2F and another
         * GeoVector2F.
         */
        inline GeoVector2F operator*=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) * *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector2F and another GeoVector2F and
         * overwrites this instance with the result.
         *
         * @details
         * An example of a Hadamard division of two two-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      2\\
         *      3
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{8}{2}\\
         *      \tfrac{6}{3}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      2
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose component act as a divisor for this vector's components.
         * @return This GeoVector2F where the components consist of the entrywise quotient of this GeoVector2F and
         * another GeoVector2F.
         */
        GeoVector2F operator/=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) / *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector2F and the provided scalar and overwrites this instance
         * with the result.
         *
         * @details
         * An example of summing up a two-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      +
         *      6
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      6\\
         *      6
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 + 6 \\
         *      6 + 6
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      14\\
         *      12
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets added up with each component of this vector.
         * @return This GeoVector2F where the components consist of the entrywise sum of this GeoVector2F and the
         * provided scalar.
         */
        inline GeoVector2F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) + other;
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector2F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of subtracting a scalar from a two-dimensional vector: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      -
         *      3
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      3\\
         *      3
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 - 3 \\
         *      6 - 3
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      5\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets subtracted from each component of this vector.
         * @return This GeoVector2F where the components consist of the entrywise difference of this GeoVector2F and the
         * provided scalar.
         */
        inline GeoVector2F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) - other;
            return *this;
        }

        /**
         * @brief Calculates the product of this GeoVector2F and the provided scalar and overwrites this instance with
         * the result.
         *
         * @details
         * An example of a multiplication between a two-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      *
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 * 4 \\
         *      6 * 4
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      32\\
         *      24
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar who get multiplied by this vector's components.
         * @return This GeoVector2F where the components consist of the product of this GeoVector2F and the provided
         * scalar.
         */
        inline GeoVector2F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) * other;
            return *this;
        }

        /**
         * @brief Calculates the quotients of a division using this GeoVector2F and the provided scalar and overwrites
         * this instance with the result.
         *
         * @details
         * An example of a division between a two-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      16\\
         *      12
         *      \end{pmatrix}
         *      /
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      16\\
         *      12
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{16}{4} \\
         *      \tfrac{12}{4}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that acts as the divisor for each component of this vector.
         * @return This GeoVector2F where the components consist of the entrywise quotient of this GeoVector2F and the
         * provided scalar.
         */
        inline GeoVector2F operator/=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) / other;
            return *this;
        }

        /**
         * @brief Rotates this vector around a given point by a given angle in degrees.
         *
         * @param angleRotationValue The angle in degrees to rotate by.
         * @param point The point that acts as this vectors origin point to rotate around.
         */
        void rotateToAngleAroundPoint(float angleRotationValue, GeoVector2F point) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                glm::rotate((*reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) -
                                                                   *reinterpret_cast<const glm::vec2*>(&point)),
                            glm::radians(angleRotationValue)) +
                *reinterpret_cast<const glm::vec2*>(&point);
        }

        /**
         * @brief Evaluates this GeoVector2F with another GeoVector2F to determine if all components are within a given
         * range of tolerance.
         *
         * @param other The other GeoVector2F whose components are evaluated against this GeoVector2F's components.
         * @param epsilonValue The vector determining the tolerance per component.
         * @return true if the difference between this vector and other vector falls within the tolerance set by the
         * epsilonValue vector, otherwise false.
         */
        bool epsilonEquals(GeoVector2F other, GeoVector2F epsilonValue) const noexcept
        {
            return glm::all(glm::equal(*reinterpret_cast<const glm::vec2*>(this),
                                       *reinterpret_cast<const glm::vec2*>(&other),
                                       *reinterpret_cast<const glm::vec2*>(&epsilonValue)));
        }

        /**
         * @brief Creates a new GeoVector2F instance with a uniform value of zero.
         *
         * @return A new GeoVector2F instance with all components set to zero.
         */
        static GeoVector2F zero() noexcept
        {
            return GeoVector2F::uniform(0);
        }

        /**
         * @brief Creates a new GeoVector2F instance with a uniform value of one.
         *
         * @return A new GeoVector2F instance with all components set to one.
         */
        static GeoVector2F one() noexcept
        {
            return GeoVector2F::uniform(1);
        }

        /**
         * @brief Creates a new uniform GeoVector2F based on the specified value.
         *
         * @param The value to use as the uniform value across the GeoVector2F.
         * @return a new GeoVector2F instance with all components set to the specified value.
         */
        static GeoVector2F uniform(float value) noexcept
        {
            return GeoVector2F(value, value);
        }
    };

    /**
     * @brief Calculates the product of the provided GeoVector2F and the provided scalar.
     *
     * @details
     * An example of a multiplication between a two-dimensional vector and a scalar: \f[
     *      4
     *      *
     *      \begin{pmatrix}
     *      8\\
     *      6
     *      \end{pmatrix}
     *      \rightarrow
     *      \begin{pmatrix}
     *      4\\
     *      4
     *      \end{pmatrix}
     *      \circ
     *      \begin{pmatrix}
     *      8\\
     *      6
     *      \end{pmatrix}
     *      =
     *      \begin{pmatrix}
     *      4 * 8 \\
     *      4 * 6
     *      \end{pmatrix}
     *      \rightarrow
     *      \begin{pmatrix}
     *      32\\
     *      24
     *      \end{pmatrix}
     * \f]
     *
     * @param lhs The scalar that gets multiplied by the GeoVector2F's components.
     * @param rhs The GeoVector2F whos components get multiplied by the scalar.
     * @return A GeoVector2F where the components consist of the product of this and the provided scalar.
     */
    inline GeoVector2F operator*(float lhs, GeoVector2F rhs) noexcept
    {
        return rhs * lhs;
    }

}

#endif //! NOVELRT_MATHS_GEOVECTOR2_H
