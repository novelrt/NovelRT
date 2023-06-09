// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR3_H
#define NOVELRT_MATHS_GEOVECTOR3_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief Represents a vector with three components.
     */
    class GeoVector3F
    {
        friend class GeoVector4F;

    private:
        GeoVector3F(glm::vec3 value) noexcept : x(value.x), y(value.y), z(value.z)
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
         * @brief The Z component of the vector.
         */
        float z;

        /**
         * @brief Creates a GeoVector3F with all components set to zero.
         *
         * @return A GeoVector3F with all components set to zero.
         */
        GeoVector3F() noexcept : x(0.0f), y(0.0f), z(0.0f)
        {
        }

        /**
         * @brief Creates a GeoVector3F with the given components.
         *
         * @param x The X component of the vector.
         * @param y The Y component of the vector.
         * @param z The Z component of the vector.
         * @return A GeoVector3F with the given components.
         */
        GeoVector3F(float x, float y, float z) noexcept : x(x), y(y), z(z)
        {
        }

        /**
         * @brief Creates a GeoVector3F based on an already existing GeoVector2F.
         *
         * @param vec2Value The GeoVector2F whose X and Y components are used for this GeoVector3F's X and Y components.
         * @return A new GeoVector3F with the given GeoVector2F X and Y components, with the Z component set to zero.
         */
        GeoVector3F(GeoVector2F vec2Value) noexcept : x(vec2Value.x), y(vec2Value.y), z(0.0f)
        {
        }

        /**
         * @brief Constructs a unit GeoVector3F with a magnitude of one by normalising this vector.
         *
         * @details
         * To normalise a vector you need to divide its components by its magnitude. As a result, a vector with the
         * resulting components will have a magnitude of 1, also known as a unit vector. \f{align*}{
         *      \vec{v}&= \begin{pmatrix}
         *      2\\
         *      6\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| &= \sqrt{v_{x}^{2} + v_{y}^{2} + v_{z}^{2}} = \sqrt{2^{2} + 6^{2} + 3^{2}}
         *      \rightarrow \sqrt{4 + 36 + 9} = \sqrt{49} = 7\\
         *      \hat{v}&=\frac{\vec{v}}{\left \| \vec{v} \right \|} = \frac{\bigl(\begin{smallmatrix}
         *      2\\
         *      6\\
         *      3
         *      \end{smallmatrix}\bigr)}{7} = \begin{pmatrix}
         *      \tfrac{2}{7}\\
         *      \tfrac{6}{7}\\
         *      \tfrac{3}{7}
         *      \end{pmatrix}\\
         *      \left \| \hat{v} \right \| &= \sqrt{\tfrac{2}{7}^{2} + \tfrac{6}{7}^{2} + \tfrac{3}{7}^{2}} =
         *      \sqrt{\tfrac{4}{49} + \tfrac{36}{49} + \tfrac{9}{49}} \rightarrow \sqrt{\tfrac{49}{49}} \rightarrow
         *      \sqrt{1} = 1
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return A unit GeoVector3F created from normalising this GeoVector3F.
         */
        [[nodiscard]] inline GeoVector3F GetNormalised() const noexcept
        {
            return GeoVector3F(glm::normalize(*reinterpret_cast<const glm::vec3*>(this)));
        }

        /**
         * @brief Calculates the magnitude of this GeoVector3F using its components. This is the same as the
         * calculating the vector's length.
         *
         * @details
         * To find a vector's magnitude you can use the Pythagorean theorem:\f{align*}{
         *      \vec{v}&= \begin{pmatrix}
         *      2\\
         *      6\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| &= \sqrt{v_{x}^{2} + v_{y}^{2} + v_{z}^{2}}
         *      &= \sqrt{2^{2} + 6^{2} + 3^{2}} \rightarrow \sqrt{4 + 36 + 9}
         *      &= \sqrt{49}
         *      &= 7
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return The magnitude of this GeoVector3F.
         */
        [[nodiscard]] inline float GetMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec3*>(this));
        }

        /**
         * @brief Calculates the length of this GeoVector3F using its components. This is the same as calculating the
         * vector's magnitude.
         *
         * @details
         * To find a vector's length you can use the Pythagorean theorem:\f{align*}{
         *      \vec{v}&= \begin{pmatrix}
         *      2\\
         *      6\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| &= \sqrt{v_{x}^{2} + v_{y}^{2} + v_{z}^{2}}
         *      &= \sqrt{2^{2} + 6^{2} + 3^{2}} \rightarrow \sqrt{4 + 36 + 9}
         *      &= \sqrt{49}
         *      &= 7
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return The length of this GeoVector3F.
         */
        [[nodiscard]] inline float GetLength() const noexcept
        {
            return GetMagnitude();
        }

        /**
         * @brief Calculates the squared magnitude of this GeoVector3F using its components. This is the same as
         * calculating the vector's squared length.
         *
         * @details
         * To find a vector's squared magnitude you can use the Pythagorean theorem:\f{align*}{
         *      \vec{v}&= \begin{pmatrix}
         *      2\\
         *      6\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \|^{2} &= v_{x}^{2} + v_{y}^{2} + v_{z}^{2}
         *      &= 2^{2} + 6^{2} + 3^{2} \rightarrow 4 + 36 + 9
         *      &= 49
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return The squared magnitude of this GeoVector3F.
         */
        [[nodiscard]] inline float GetSquaredMagnitude() const noexcept
        {
            return glm::dot(*reinterpret_cast<const glm::vec3*>(this), *reinterpret_cast<const glm::vec3*>(this));
        }

        /**
         * @brief Calculates the squared length of this GeoVector3F using its components. This is the same as
         * calculating the vector's squared magnitude.
         *
         * @details
         * To find a vector's squared length you can use the Pythagorean theorem:\f{align*}{
         *      \vec{v}&= \begin{pmatrix}
         *      2\\
         *      6\\
         *      3
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \|^{2} &= v_{x}^{2} + v_{y}^{2} + v_{z}^{2}
         *      &= 2^{2} + 6^{2} + 3^{2} \rightarrow 4 + 36 + 9
         *      &= 49
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return The squared length of this GeoVector3F.
         */
        [[nodiscard]] inline float GetSquaredLength() const noexcept
        {
            return GetSquaredMagnitude();
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if all components match.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @returns true if all components matched, otherwise false.
         */
        [[nodiscard]] inline bool operator==(const GeoVector3F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec3*>(this) == *reinterpret_cast<const glm::vec3*>(&other);
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if all components do not match.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @returns true if any of the components do not match, otherwise false.
         */
        [[nodiscard]] inline bool operator!=(const GeoVector3F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec3*>(this) != *reinterpret_cast<const glm::vec3*>(&other);
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if any of its components is less
         * than the other GeoVector3F's components.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @return true if any of the components is less than the other GeoVector3F's components, otherwise false.
         */
        [[nodiscard]] inline bool operator<(const GeoVector3F& other) const noexcept
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec3*>(this), *reinterpret_cast<const glm::vec3*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if any of its components is less
         * than or equal to the other GeoVector3F's components.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @return true if any of the components is less than or equal to the other GeoVector3F's components,
         * otherwise false.
         */
        [[nodiscard]] inline bool operator<=(const GeoVector3F& other) const noexcept
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec3*>(this),
                                               *reinterpret_cast<const glm::vec3*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if any of its components is greater
         * than the other GeoVector3F's components.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @return true if any of the components is greater than the other GeoVector3F's components, otherwise false.
         */
        [[nodiscard]] inline bool operator>(const GeoVector3F& other) const noexcept
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec3*>(this),
                                             *reinterpret_cast<const glm::vec3*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if any of its components is greater
         * than or equal to the other GeoVector3F's components.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @return true if any of the components is greater than or equal to the other GeoVector3F's components,
         * otherwise false.
         */
        [[nodiscard]] inline bool operator>=(const GeoVector3F& other) const noexcept
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec3*>(this),
                                                  *reinterpret_cast<const glm::vec3*>(&other)));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector3F and another GeoVector3F.
         *
         * @details
         * An example of an entrywise addition using three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      2 + 4\\
         *      3 + 5\\
         *      4 + 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      6\\
         *      8\\
         *      10
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other vector whose components get added together with this vector.
         * @return A GeoVector3F where the components consist of the entrywise sum of this GeoVector3F and another
         * GeoVector3F.
         */
        [[nodiscard]] inline GeoVector3F operator+(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) + *reinterpret_cast<const glm::vec3*>(&other));
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector3F and another GeoVector3F.
         *
         * @details
         * An example of an entrywise subtraction using three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      1\\
         *      4\\
         *      6
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      2 - 1\\
         *      3 - 4\\
         *      4 - 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      1\\
         *      -1\\
         *      -2
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other vector whose components get subtracted from this vector.
         * @return A GeoVector3F where the components consist of the entrywise difference of this GeoVector3F and
         * another GeoVector3F.
         */
        [[nodiscard]] inline GeoVector3F operator-(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&other));
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector3F and another GeoVector3F.
         *
         * @details
         * An example of a Hadamard product of two three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      2 \times 4\\
         *      3 \times 5\\
         *      4 \times 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8\\
         *      15\\
         *      24
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other vector whose components get multiplied by this vector's components.
         * @return A GeoVector3F where the components consist of the Hadamard product of this GeoVector3F and another
         * GeoVector3F.
         */
        [[nodiscard]] inline GeoVector3F operator*(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) * *reinterpret_cast<const glm::vec3*>(&other));
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector3F and another GeoVector3F.
         *
         * @details
         * An example of a Hadamard division of two three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      20
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      \tfrac{8}{2}\\
         *      \tfrac{6}{3}\\
         *      \tfrac{20}{4}
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      4\\
         *      2\\
         *      5
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other vector whose components act as a divisor for this vector's components.
         * @return A GeoVector3F where the components consist of the entrywise quotient of this GeoVector3F and another
         * GeoVector3F.
         */
        [[nodiscard]] GeoVector3F operator/(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) / *reinterpret_cast<const glm::vec3*>(&other));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector3F and the provided scalar.
         *
         * @details
         * An example of summing up a three-dimensional vector and a scalar: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      +
         *      6
         *      &\rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      6\\
         *      6\\
         *      6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8 + 6 \\
         *      6 + 6 \\
         *      3 + 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      14\\
         *      12\\
         *      9
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other scalar that gets added up with each component of this vector.
         * @return A GeoVector3F where the components consist of the entrywise sum of this GeoVector3F and the provided
         * scalar.
         */
        [[nodiscard]] inline GeoVector3F operator+(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) + other);
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector3F and the provided scalar.
         *
         * @details
         * An example of subtracting a scalar from a three-dimensional vector: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      -
         *      3
         *      &\rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      3\\
         *      3\\
         *      3
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8 - 3 \\
         *      6 - 3 \\
         *      3 - 3
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      5\\
         *      3\\
         *      0
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other scalar that gets subtracted from each component of this vector.
         * @return A GeoVector3F where the components consist of the entrywise difference of this GeoVector3F and the
         * provided scalar.
         */
        [[nodiscard]] inline GeoVector3F operator-(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) - other);
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector3F and the provided scalar.
         *
         * @details
         * An example of a multiplication between a three-dimensional vector and a scalar: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      \times
         *      4
         *      &\rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8 \times 4 \\
         *      6 \times 4 \\
         *      3 \times 4
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      32\\
         *      24\\
         *      12
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other scalar who get multiplied by this vector's components.
         * @return A GeoVector3F where the components consist of the Hadamard product of this GeoVector3F and the
         * provided scalar.
         */
        [[nodiscard]] inline GeoVector3F operator*(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) * other);
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector3F and the provided scalar.
         *
         * @details
         * An example of a division between a three-dimensional vector and a scalar: \f{align*}{
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8
         *      \end{pmatrix}
         *      /
         *      4
         *      &\rightarrow
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      \tfrac{16}{4} \\
         *      \tfrac{12}{4} \\
         *      \tfrac{8}{4}
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      4\\
         *      3\\
         *      2
         *      \end{pmatrix}
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other scalar that acts as the divisor for each component of this vector.
         * @return A GeoVector3F where the components consist of the entrywise quotient of this GeoVector3F and the
         * provided scalar.
         */
        [[nodiscard]] GeoVector3F operator/(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) / other);
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector3F and another GeoVector3F and overwrites this instance
         * with the result.
         *
         * @details
         * An example of an entrywise addition using three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      2 + 4\\
         *      3 + 5\\
         *      4 + 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      6\\
         *      8\\
         *      10
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other vector whose components get added together with this vector.
         * @return This GeoVector3F where the components consist of the entrywise sum of this GeoVector3F and another
         * GeoVector3F.
         */
        inline GeoVector3F& operator+=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) + *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector3F and another GeoVector3F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of an entrywise subtraction using three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      1\\
         *      4\\
         *      6
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      2 - 1\\
         *      3 - 4\\
         *      4 - 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      1\\
         *      -1\\
         *      -2
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other vector whose components get subtracted from this vector.
         * @return This GeoVector3F where the components consist of the entrywise difference of this GeoVector3F and
         * another GeoVector3F.
         */
        inline GeoVector3F& operator-=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector3F and another GeoVector3F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a Hadamard product of two three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      2 \times 4\\
         *      3 \times 5\\
         *      4 \times 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8\\
         *      15\\
         *      24
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other vector whose components get multiplied by this vector's components.
         * @return This GeoVector3F where the components consist of the Hadamard product of this GeoVector3F and another
         * GeoVector3F.
         */
        inline GeoVector3F operator*=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) * *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector3F and another GeoVector3F and
         * overwrites this instance with the result.
         *
         * @details
         * An example of a Hadamard division of two three-dimensional vectors: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      20
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}
         *      &=
         *      \begin{pmatrix}
         *      \tfrac{8}{2}\\
         *      \tfrac{6}{3}\\
         *      \tfrac{20}{4}
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      4\\
         *      2\\
         *      5
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other vector whose components act as a divisor for this vector's components.
         * @return This GeoVector3F where the components consist of the entrywise quotient of this GeoVector3F and
         * another GeoVector3F.
         */
        GeoVector3F operator/=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) / *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector3F and the provided scalar and overwrites this instance
         * with the result.
         *
         * @details
         * An example of summing up a three-dimensional vector and a scalar: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      +
         *      6
         *      &\rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      6\\
         *      6\\
         *      6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8 + 6 \\
         *      6 + 6 \\
         *      3 + 6
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      14\\
         *      12\\
         *      9
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other scalar that gets added up with each component of this vector.
         * @return This GeoVector3F where the components consist of the entrywise sum of this GeoVector3F and the
         * provided scalar.
         */
        inline GeoVector3F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) + other;
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector3F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of subtracting a scalar from a three-dimensional vector: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      -
         *      3
         *      &\rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      3\\
         *      3\\
         *      3
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8 - 3 \\
         *      6 - 3 \\
         *      3 - 3
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      5\\
         *      3\\
         *      0
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other scalar that gets subtracted from each component of this vector.
         * @return This GeoVector3F where the components consist of the entrywise difference of this GeoVector3F and the
         * provided scalar.
         */
        inline GeoVector3F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) - other;
            return *this;
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector3F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a multiplication between a three-dimensional vector and a scalar: \f{align*}{
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      \times
         *      4
         *      &\rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      8 \times 4 \\
         *      6 \times 4 \\
         *      3 \times 4
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      32\\
         *      24\\
         *      12
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other scalar who get multiplied by this vector's components.
         * @return This GeoVector3F where the components consist of the Hadamard product of this GeoVector3F and the
         * provided scalar.
         */
        inline GeoVector3F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) * other;
            return *this;
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector3F and the provided scalar and
         * overwrites this instance with the result.
         *
         * @details
         * An example of a division between a three-dimensional vector and a scalar: \f{align*}{
         *      \begin{pmatrix}
         *      16\\
         *      12
         *      8
         *      \end{pmatrix}
         *      /
         *      4
         *      &\rightarrow
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      \tfrac{16}{4} \\
         *      \tfrac{12}{4} \\
         *      \tfrac{8}{4}
         *      \end{pmatrix}\\
         *      &=
         *      \begin{pmatrix}
         *      4\\
         *      3\\
         *      2
         *      \end{pmatrix}
         * \f}
         *
         * @param other The other scalar that acts as the divisor for each component of this vector.
         * @return This GeoVector3F where the components consist of the entrywise quotient of this GeoVector3F and the
         * provided scalar.
         */
        GeoVector3F operator/=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) / other;
            return *this;
        }

        /**
         * @brief Rotates this vector around a given point by a given angle in degrees.
         *
         * @param angleRotationValue The angle in degrees to rotate by.
         * @param point The point that acts as this vectors origin point to rotate around.
         * @param axis The axis on which this rotation will be applied.
         */
        void RotateToAngleAroundPointDeg(float angleRotationValue,
                                         const GeoVector3F& point,
                                         const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept
        {
            RotateToAngleAroundPointRad(glm::radians(angleRotationValue), point, axis);
        }

        /**
         * @brief Rotates this vector around a given point by a given angle in radians.
         *
         * @param angleRotationValue The angle in radians to rotate by.
         * @param point The point that acts as this vectors origin point to rotate around.
         * @param axis The axis on which this rotation will be applied.
         */
        void RotateToAngleAroundPointRad(float angleRotationValue,
                                         const GeoVector3F& point,
                                         const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                glm::rotate(*reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&point),
                            angleRotationValue, *reinterpret_cast<const glm::vec3*>(&axis)) +
                *reinterpret_cast<const glm::vec3*>(&point);
        }

        /**
         * @brief Evaluates this GeoVector3F with another GeoVector3F to determine if all components are within a given
         * range of tolerance.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other GeoVector3F whose components are evaluated against this GeoVector3F's components.
         * @param epsilonValue The vector determining the tolerance per component.
         * @return true if the difference between this vector and other vector falls within the tolerance set by the
         * epsilonValue vector, otherwise false.
         */
        [[nodiscard]] bool EpsilonEquals(const GeoVector3F& other, const GeoVector3F& epsilonValue) const noexcept
        {
            return glm::all(glm::equal(*reinterpret_cast<const glm::vec3*>(this),
                                       *reinterpret_cast<const glm::vec3*>(&other),
                                       *reinterpret_cast<const glm::vec3*>(&epsilonValue)));
        }

        /**
         * @brief Returns the sum of products of this GeoVector3Fs components and the other GeoVector3Fs components.
         *
         * @details
         * The calculation used to obtain the dot product can be seen in this example: \f{align*}{
         *      \vec{u} &= \begin{pmatrix}
         *      2\\
         *      3\\
         *      4
         *      \end{pmatrix}\\
         *      \vec{v} &= \begin{pmatrix}
         *      4\\
         *      5\\
         *      6
         *      \end{pmatrix}\\
         *      \vec{u}\cdot \vec{v} &= \vec{u}_{x} \times \vec{v}_{x} + \vec{u}_{y} \times \vec{v}_{y} +
         *      \vec{v}_{z}\times \vec{v}_{z} \\
         *      &= 2 \times 4 + 3 \times 5 + 4 \times 6\\
         *      &= 8 + 15 + 24\\
         *      &= 47
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other GeoVector3F, the components of which get multiplied and summed up with this
         * GeoVector3F.
         * @return The sum of products of the left-hand side GeoVector3Fs components and the right-hand side
         * GeoVector3Fs components.
         */
        [[nodiscard]] inline float Dot(GeoVector3F other) noexcept
        {
            return glm::dot(*reinterpret_cast<const glm::vec3*>(this),
                            NovelRT::Core::Utilities::Misc::BitCast<glm::vec3>(other));
        }

        /**
         * @brief Calculates the cross product of this GeoVector3F with another GeoVector3F. The magnitude of the
         * resulting vector is equal to the area of a parallelogram with this GeoVector3F and the other GeoVector3F as
         * sides.
         *
         * @details
         * To calculate the cross product of two vectors you take the following steps: \f{align*}{
         *      \vec{a} &= \begin{pmatrix}
         *      1\\
         *      5\\
         *      7
         *      \end{pmatrix}\\
         *      \vec{b} &= \begin{pmatrix}
         *      1\\
         *      2\\
         *      3
         *      \end{pmatrix}\\
         *      \vec{c} &= \begin{pmatrix}
         *      \vec{a}_{y}\vec{b}_{z} - \vec{a}_{z}\vec{b}_{y}\\
         *      \vec{a}_{z}\vec{b}_{x} - \vec{a}_{x}\vec{b}_{z}\\
         *      \vec{a}_{x}\vec{b}_{y} - \vec{a}_{y}\vec{b}_{x}
         *      \end{pmatrix}\\
         *      &= \begin{pmatrix}
         *      5 \times 3 - 7 \times 2\\
         *      7 \times 1 - 1 \times 3\\
         *      1 \times 2 - 5 \times 1
         *      \end{pmatrix} \rightarrow
         *      \begin{pmatrix}
         *      15 - 14\\
         *      7 - 3\\
         *      2 - 5
         *      \end{pmatrix}\\
         *      &= \begin{pmatrix}
         *      1\\
         *      4\\
         *      -3
         *      \end{pmatrix}
         * \f}
         * It should be noted that by flipping the left hand side vector with the right hand side vector will result in
         * a cross product of equal length with opposite polarity.
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other GeoVector3F, the components of which will be used to calculate the cross product with
         * this GeoVector3F.
         * @return The cross product of this GeoVector3F with another GeoVector3F.
         */
        [[nodiscard]] inline GeoVector3F Cross(GeoVector3F other) noexcept
        {
            return GeoVector3F(
                glm::cross(*reinterpret_cast<glm::vec3*>(this), NovelRT::Core::Utilities::Misc::BitCast<glm::vec3>(other)));
        }

        /**
         * @brief Calculates the distance between this GeoVector3F and another GeoVector3F.
         *
         * @details
         * The calculation used to obtain the distance can be seen in this example: \f{align*}{
         *      \vec{v}_{1} &= \begin{pmatrix}
         *      6\\
         *      8\\
         *      3
         *      \end{pmatrix}\\
         *      \vec{v}_{2} &= \begin{pmatrix}
         *      10\\
         *      12\\
         *      5
         *      \end{pmatrix}\\
         *      \vec{\Delta v} &= \vec{v}_{2} - \vec{v}_{1}\\
         *      &=\begin{pmatrix}
         *      10 - 6\\
         *      12 - 8\\
         *      5 - 2
         *      \end{pmatrix} \\
         *      &= \begin{pmatrix}
         *      4\\
         *      4\\
         *      2
         *      \end{pmatrix}\\
         *      \left \| \vec{\Delta v} \right \| &= \sqrt{{\Delta v}_x^2 + {\Delta v}_y^2 + {\Delta v}_z^2}\\
         *      &= \sqrt{4^2 + 4^2 + 2^2} \rightarrow \sqrt{16 + 16 + 4}\\
         *      &= \sqrt{36}\\
         *      &= 6
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other point to measure the distance to.
         * @return The distance between this GeoVector3F and another GeoVector3F.
         */
        [[nodiscard]] inline float Distance(GeoVector3F other) noexcept
        {
            return glm::distance(*reinterpret_cast<const glm::vec3*>(this),
                                 NovelRT::Core::Utilities::Misc::BitCast<glm::vec3>(other));
        }

        /**
         * @brief Calculates the squared distance between this GeoVector3F and another GeoVector3F.
         *
         * @details
         * The calculation used to obtain the squared distance can be seen in this example: \f{align*}{
         *      \vec{v}_{1} &= \begin{pmatrix}
         *      6\\
         *      8\\
         *      3
         *      \end{pmatrix}\\
         *      \vec{v}_{2} &= \begin{pmatrix}
         *      10\\
         *      12\\
         *      5
         *      \end{pmatrix}\\
         *      \vec{\Delta v} &= \vec{v}_{2} - \vec{v}_{1}\\
         *      &=\begin{pmatrix}
         *      10 - 6\\
         *      12 - 8\\
         *      5 - 2
         *      \end{pmatrix} \\
         *      &= \begin{pmatrix}
         *      4\\
         *      4\\
         *      2
         *      \end{pmatrix}\\
         *      \left \| \vec{\Delta v} \right \|^2 &= {\Delta v}_x^2 + {\Delta v}_y^2 + {\Delta v}_z^2\\
         *      &= 4^2 + 4^2 + 2^2 \rightarrow 16 + 16 + 4\\
         *      &= 36
         * \f}
         *
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param other The other point to measure the squared distance to.
         * @return The squared distance between this GeoVector3F and another GeoVector3F.
         */
        [[nodiscard]] inline float SquaredDistance(GeoVector3F other) noexcept
        {
            return (*this - other).GetSquaredMagnitude();
        }

        /**
         * @brief Creates a new GeoVector3F instance with a uniform value of zero.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return A new GeoVector3F instance with all components set to zero.
         */
        [[nodiscard]] static GeoVector3F Zero() noexcept
        {
            return GeoVector3F::Uniform(0);
        }

        /**
         * @brief Creates a new GeoVector3F instance with a uniform value of one.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @return A new GeoVector3F instance with all components set to one.
         */
        [[nodiscard]] static GeoVector3F One() noexcept
        {
            return GeoVector3F::Uniform(1);
        }

        /**
         * @brief Creates a new uniform GeoVector3F based on the specified value.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and can introduce overhead for
         * calling the method.
         *
         * @param value The value to use as the uniform value across the GeoVector3F.
         * @return a new GeoVector3F instance with all components set to the specified value.
         */
        [[nodiscard]] static GeoVector3F Uniform(float value) noexcept
        {
            return GeoVector3F(value, value, value);
        }
    };

    /**
     * @brief Calculates the product of the provided GeoVector3F and the provided scalar.
     *
     * @details
     * An example of a multiplication between a three-dimensional vector and a scalar: \f{align*}{
     *      4
     *      \times
     *      \begin{pmatrix}
     *      8\\
     *      6\\
     *      3
     *      \end{pmatrix}
     *      &\rightarrow
     *      \begin{pmatrix}
     *      4\\
     *      4\\
     *      4
     *      \end{pmatrix}
     *      \circ
     *      \begin{pmatrix}
     *      8\\
     *      6\\
     *      3
     *      \end{pmatrix}\\
     *      &=
     *      \begin{pmatrix}
     *      4 \times 8 \\
     *      4 \times 6 \\
     *      4 \times 3
     *      \end{pmatrix}\\
     *      &=
     *      \begin{pmatrix}
     *      32\\
     *      24\\
     *      12
     *      \end{pmatrix}
     * \f}
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param lhs The scalar that gets multiplied by the GeoVector3F's components.
     * @param rhs The GeoVector3F whose components get multiplied by the scalar.
     * @return A GeoVector3F where the components consist of the product of this and the provided scalar.
     */
    [[nodiscard]] inline GeoVector3F operator*(float lhs, const GeoVector3F& rhs) noexcept
    {
        return rhs * lhs;
    }
}

#endif //! NOVELRT_MATHS_GEOVECTOR3_H
