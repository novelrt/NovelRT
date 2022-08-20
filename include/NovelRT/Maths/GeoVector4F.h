// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR4_H
#define NOVELRT_MATHS_GEOVECTOR4_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief Represents a vector with four components.
     */
    class GeoVector4F
    {
        friend class GeoMatrix4x4F;

    private:
        GeoVector4F(glm::vec4 value) noexcept : x(value.x), y(value.y), z(value.z), w(value.w)
        {
        }

        inline const glm::vec4& vec4Value() const noexcept
        {
            return *reinterpret_cast<const glm::vec4*>(this);
        }

        inline glm::vec4& vec4Value() noexcept
        {
            return reinterpret_cast<glm::vec4&>(*this);
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
         * @brief The W component of the vector.
         */
        float w;

        /**
         * @brief Creates a GeoVector4F with all components set to zero.
         *
         * @return A GeoVector4F with all components set to zero.
         */
        GeoVector4F() noexcept
        {
        }

        /**
         * @brief Creates a GeoVector4F with the given components.
         *
         * @param x The X component of the vector.
         * @param y The Y component of the vector.
         * @param z The Z component of the vector.
         * @param w The W component of the vector.
         * @return A GeoVector4F with the given components.
         */
        GeoVector4F(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w)
        {
        }

        /**
         * @brief Creates a GeoVector4F with the given GeoVector2F.
         *
         * @param vec2Value The GeoVector2F whose X and Y components are used for the GeoVector4F X and Y components.
         * @return A GeoVector4F with the given GeoVector2F and the Z and W components set to zero.
         */
        GeoVector4F(GeoVector2F vec2Value) noexcept : x(vec2Value.x), y(vec2Value.y), z(0.0f), w(0.0f)
        {
        }

        /**
         * @brief Creates a GeoVector4F with the given GeoVector3F.
         *
         * @param vec3Value The GeoVector2F whose X, Y and Z components are used for the GeoVector4F X, Y and Z
         * components.
         * @return A GeoVector4F with the given GeoVector3F and the W component set to zero.
         */
        GeoVector4F(const GeoVector3F& vec3Value) noexcept : x(vec3Value.x), y(vec3Value.y), z(vec3Value.z), w(0.f)
        {
        }

        /**
         * @brief Constructs a unit GeoVector4F with a magnitude of one by normalising this vector.
         *
         * @details
         * To calculate a vector's unit vector you first calculate its magnitude and then divide the vector by its
         * magnitude \f[
         *      \vec{v}= \begin{pmatrix}
         *      7\\
         *      2\\
         *      10\\
         *      4
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| = \sqrt{v_{x}^{2} + v_{y}^{2} + v_{z}^{2}} = \sqrt{7^{2} + 2^{2} + 10^{2} +
         *      4^{2}}
         *      \rightarrow \sqrt{49 + 4 + 100 + 16} = \sqrt{169} = 13\\
         *      \hat{v}=\frac{\vec{v}}{\left \| \vec{v} \right \|} = \frac{\bigl(\begin{smallmatrix}
         *      7\\
         *      2\\
         *      10\\
         *      4
         *      \end{smallmatrix}\bigr)}{13} = \begin{pmatrix}
         *      \tfrac{7}{13}\\
         *      \tfrac{2}{13}\\
         *      \tfrac{10}{13}\\
         *      \tfrac{4}{13}
         *      \end{pmatrix}\\
         *      \left \| \hat{v} \right \| = \sqrt{\tfrac{7}{13}^{2} + \tfrac{2}{13}^{2} + \tfrac{10}{13}^{2} +
         *      \tfrac{4}{13}^{2}} = \sqrt{\tfrac{49}{169} + \tfrac{4}{169} + \tfrac{100}{169} + \tfrac{16}{169}}
         *      \rightarrow \sqrt{\tfrac{169}{169}} \rightarrow \sqrt{1} = 1 \f]
         *
         * @return A unit GeoVector4F created from normalising this GeoVector4F.
         */
        inline GeoVector4F getNormalised() const noexcept
        {
            return GeoVector4F(glm::normalize(vec4Value()));
        }

        /**
         * @brief Calculates the magnitude of this GeoVector4F using its components. This is the same as the
         * calculating the vector's length.
         *
         * @details
         * To find a vector's magnitude you can use the Pythagorean theorem:\f[
         *      \vec{v}= \begin{pmatrix}
         *      7\\
         *      2\\
         *      10\\
         *      4
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| = \sqrt{v_{x}^{2} + v_{y}^{2} + v_{z}^{2}} = \sqrt{7^{2} + 2^{2} + 10^{2} +
         *      4^{2}}
         *      \rightarrow \sqrt{49 + 4 + 100 + 16} = \sqrt{169} = 13
         * \f]
         * @return The magnitude of this GeoVector4F.
         */
        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec4*>(this));
        }

        /**
         * @brief Calculates the length of this GeoVector4F using its components. This is the same as calculating the
         * vector's magnitude.
         *
         * @details
         * To find a vector's length you can use the Pythagorean theorem:\f[
         *      \vec{v}= \begin{pmatrix}
         *      7\\
         *      2\\
         *      10\\
         *      4
         *      \end{pmatrix}\\
         *      \left \| \vec{v} \right \| = \sqrt{v_{x}^{2} + v_{y}^{2} + v_{z}^{2}} = \sqrt{7^{2} + 2^{2} + 10^{2} +
         *      4^{2}}
         *      \rightarrow \sqrt{49 + 4 + 100 + 16} = \sqrt{169} = 13
         * \f]
         * @return The length of this GeoVector4F.
         */
        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if all components match.
         *
         * @param other The GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @returns true if all components matched, otherwise false.
         */
        inline bool operator==(const GeoVector4F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec4*>(this) == *reinterpret_cast<const glm::vec4*>(&other);
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if all components do not match.
         *
         * @param other The GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @returns true if any of the components do not match, otherwise false.
         */
        inline bool operator!=(const GeoVector4F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec4*>(this) != *reinterpret_cast<const glm::vec4*>(&other);
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if any of its components is less
         * than the other's components.
         *
         * @param other The GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @return true if any of the components is less than the other GeoVector4F's components, otherwise false.
         */
        inline bool operator<(const GeoVector4F& other) const noexcept
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec4*>(this), *reinterpret_cast<const glm::vec4*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if any of its components is less
         * than or equal to the other's components.
         *
         * @param other The GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @return true if any of the components is less than or equal to the other GeoVector4F's components,
         * otherwise false.
         */
        inline bool operator<=(const GeoVector4F& other) const noexcept
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec4*>(this),
                                               *reinterpret_cast<const glm::vec4*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if any of its components is greater
         * than the other's components.
         *
         * @param other The GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @return true if any of the components is greater than the other GeoVector4F's components, otherwise false.
         */
        inline bool operator>(const GeoVector4F& other) const noexcept
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec4*>(this),
                                             *reinterpret_cast<const glm::vec4*>(&other)));
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if any of its components is greater
         * than or equal to the other's components.
         *
         * @param other The GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @return true if any of the components is greater than or equal to the other GeoVector4F's components,
         * otherwise false.
         */
        inline bool operator>=(const GeoVector4F& other) const noexcept
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec4*>(this),
                                                  *reinterpret_cast<const glm::vec4*>(&other)));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector4F and another GeoVector4F.
         *
         * @details
         * An example of an entrywise addition using four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6\\
         *      7
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 + 4\\
         *      3 + 5\\
         *      4 + 6\\
         *      5 + 7
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      6\\
         *      8\\
         *      10\\
         *      12
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get added together with this vector.
         * @return A GeoVector4F where the components consist of the entrywise sum of this GeoVector4F and another
         * GeoVector4F.
         */
        inline GeoVector4F operator+(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) + *reinterpret_cast<const glm::vec4*>(&other));
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector4F and another GeoVector4F.
         *
         * @details
         * An example of an entrywise subtraction using four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      1\\
         *      4\\
         *      6\\
         *      2
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 - 1\\
         *      3 - 4\\
         *      4 - 6\\
         *      5 - 2
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      1\\
         *      -1\\
         *      -2\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get subtracted from this vector.
         * @return A GeoVector4F where the components consist of the entrywise difference of this GeoVector4F and
         * another GeoVector4F.
         */
        inline GeoVector4F operator-(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) - *reinterpret_cast<const glm::vec4*>(&other));
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector4F and another GeoVector4F.
         *
         * @details
         * An example of a Hadamard product of two four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6\\
         *      7
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 \times 4\\
         *      3 \times 5\\
         *      4 \times 6\\
         *      5 \times 7
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      15\\
         *      24\\
         *      35
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get multiplied by this vector's components.
         * @return A GeoVector4F where the components consist of the Hadamard product of this GeoVector4F and another
         * GeoVector4F.
         */
        inline GeoVector4F operator*(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) * *reinterpret_cast<const glm::vec4*>(&other));
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector4F and another GeoVector4F.
         *
         * @details
         * An example of a Hadamard division of two four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      20\\
         *      15
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{8}{2}\\
         *      \tfrac{6}{3}\\
         *      \tfrac{20}{4}\\
         *      \tfrac{15}{5}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      2\\
         *      5\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose component act as a divisor for this vector's components.
         * @return A GeoVector4F where the components consist of the entrywise quotient of this GeoVector4F and another
         * GeoVector4F.
         */
        GeoVector4F operator/(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) / *reinterpret_cast<const glm::vec4*>(&other));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector4F and the provided scalar.
         *
         * @details
         * An example of summing up a four-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      5
         *      \end{pmatrix}
         *      +
         *      6
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      5
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      6\\
         *      6\\
         *      6\\
         *      6
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 + 6 \\
         *      6 + 6 \\
         *      3 + 6 \\
         *      5 + 6
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      14\\
         *      12\\
         *      9\\
         *      11
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets added up with each component of this vector.
         * @return A GeoVector4F where the components consist of the entrywise sum of this GeoVector4F and the provided
         * scalar.
         */
        inline GeoVector4F operator+(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) + other);
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector4F and the provided scalar.
         *
         * @details
         * An example of subtracting a scalar from a three-dimensional vector: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      -
         *      3
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      3\\
         *      3\\
         *      3\\
         *      3
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 - 3 \\
         *      6 - 3 \\
         *      3 - 3 \\
         *      7 - 3
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      5\\
         *      3\\
         *      0\\
         *      4
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets subtracted from each component of this vector.
         * @return A GeoVector4F where the components consist of the entrywise difference of this GeoVector4F and the
         * provided scalar.
         */
        inline GeoVector4F operator-(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) - other);
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector4F and the provided scalar.
         *
         * @details
         * An example of a multiplication between a three-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      \times
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 \times 4 \\
         *      6 \times 4 \\
         *      3 \times 4 \\
         *      7 \times 4
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      32\\
         *      24\\
         *      12\\
         *      28
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar who get multiplied by this vector's components.
         * @return A GeoVector4F where the components consist of the Hadamard product of this GeoVector4F and the
         * provided scalar.
         */
        inline GeoVector4F operator*(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) * other);
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector4F and the provided scalar.
         *
         * @details
         * An example of a division between a four-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8\\
         *      28
         *      \end{pmatrix}
         *      /
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8\\
         *      28
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{16}{4} \\
         *      \tfrac{12}{4} \\
         *      \tfrac{8}{4} \\
         *      \tfrac{28}{4}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      3\\
         *      2\\
         *      7
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that acts as the divisor for each component of this vector.
         * @return A GeoVector4F where the components consist of the entrywise quotient of this GeoVector4F and the
         * provided scalar.
         */
        GeoVector4F operator/(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) / other);
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector4F and another GeoVector4F and overwrites this instance
         * with the result.
         *
         * @details
         * An example of an entrywise addition using four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6\\
         *      7
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 + 4\\
         *      3 + 5\\
         *      4 + 6\\
         *      5 + 7
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      6\\
         *      8\\
         *      10\\
         *      12
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get added together with this vector.
         * @return This GeoVector4F where the components consist of the entrywise sum of this GeoVector4F and another
         * GeoVector4F.
         */
        inline GeoVector4F& operator+=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) += *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector4F and another GeoVector4F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of an entrywise subtraction using four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      1\\
         *      4\\
         *      6\\
         *      2
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 - 1\\
         *      3 - 4\\
         *      4 - 6\\
         *      5 - 2
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      1\\
         *      -1\\
         *      -2\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get subtracted from this vector.
         * @return This GeoVector4F where the components consist of the entrywise difference of this GeoVector4F and
         * another GeoVector4F.
         */
        inline GeoVector4F& operator-=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) -= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector4F and another GeoVector4F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a Hadamard product of two four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      5\\
         *      6\\
         *      7
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      2 \times 4\\
         *      3 \times 5\\
         *      4 \times 6\\
         *      5 \times 7
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      15\\
         *      24\\
         *      35
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose components get multiplied by this vector's components.
         * @return This GeoVector4F where the components consist of the Hadamard product of this GeoVector4F and another
         * GeoVector4F.
         */
        inline GeoVector4F operator*=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) *= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector4F and another GeoVector4F and
         * overwrites this instance with the result.
         *
         * @details
         * An example of a Hadamard division of two four-dimensional vectors: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      20\\
         *      15
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      2\\
         *      3\\
         *      4\\
         *      5
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{8}{2}\\
         *      \tfrac{6}{3}\\
         *      \tfrac{20}{4}\\
         *      \tfrac{15}{5}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      2\\
         *      5\\
         *      3
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other vector whose component act as a divisor for this vector's components.
         * @return This GeoVector4F where the components consist of the entrywise quotient of this GeoVector4F and
         * another GeoVector4F.
         */
        GeoVector4F operator/=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) /= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise sum of this GeoVector4F and the provided scalar and overwrites this instance
         * with the result.
         *
         * @details
         * An example of summing up a four-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      5
         *      \end{pmatrix}
         *      +
         *      6
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      5
         *      \end{pmatrix}
         *      +
         *      \begin{pmatrix}
         *      6\\
         *      6\\
         *      6\\
         *      6
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 + 6 \\
         *      6 + 6 \\
         *      3 + 6 \\
         *      5 + 6
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      14\\
         *      12\\
         *      9\\
         *      11
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets added up with each component of this vector.
         * @return This GeoVector4F where the components consist of the entrywise sum of this GeoVector4F and the
         * provided scalar.
         */
        inline GeoVector4F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) += other;
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoVector4F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of subtracting a scalar from a three-dimensional vector: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      -
         *      3
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      -
         *      \begin{pmatrix}
         *      3\\
         *      3\\
         *      3\\
         *      3
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 - 3 \\
         *      6 - 3 \\
         *      3 - 3 \\
         *      7 - 3
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      5\\
         *      3\\
         *      0\\
         *      4
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that gets subtracted from each component of this vector.
         * @return This GeoVector4F where the components consist of the entrywise difference of this GeoVector4F and the
         * provided scalar.
         */
        inline GeoVector4F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) -= other;
            return *this;
        }

        /**
         * @brief Calculates the Hadamard product of this GeoVector4F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a multiplication between a three-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      \times
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      8\\
         *      6\\
         *      3\\
         *      7
         *      \end{pmatrix}
         *      \circ
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      8 \times 4 \\
         *      6 \times 4 \\
         *      3 \times 4 \\
         *      7 \times 4
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      32\\
         *      24\\
         *      12\\
         *      28
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar who get multiplied by this vector's components.
         * @return This GeoVector4F where the components consist of the Hadamard product of this GeoVector4F and the
         * provided scalar.
         */
        inline GeoVector4F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) *= other;
            return *this;
        }

        /**
         * @brief Calculates the quotients of a Hadamard division using this GeoVector4F and the provided scalar and
         * overwrites this instance with the result.
         *
         * @details
         * An example of a division between a four-dimensional vector and a scalar: \f[
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8\\
         *      28
         *      \end{pmatrix}
         *      /
         *      4
         *      \rightarrow
         *      \begin{pmatrix}
         *      16\\
         *      12\\
         *      8\\
         *      28
         *      \end{pmatrix}
         *      \oslash
         *      \begin{pmatrix}
         *      4\\
         *      4\\
         *      4\\
         *      4
         *      \end{pmatrix}
         *      =
         *      \begin{pmatrix}
         *      \tfrac{16}{4} \\
         *      \tfrac{12}{4} \\
         *      \tfrac{8}{4} \\
         *      \tfrac{28}{4}
         *      \end{pmatrix}
         *      \rightarrow
         *      \begin{pmatrix}
         *      4\\
         *      3\\
         *      2\\
         *      7
         *      \end{pmatrix}
         * \f]
         *
         * @param other The other scalar that acts as the divisor for each component of this vector.
         * @return This GeoVector4F where the components consist of the entrywise quotient of this GeoVector4F and the
         * provided scalar.
         */
        GeoVector4F operator/=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) /= other;
            return *this;
        }

        /**
         * @brief Rotates this vector around a given point by a given angle in degrees.
         *
         * @param angleRotationValue The angle in degrees to rotate by.
         * @param point The point that acts as this vectors origin point to rotate around.
         * @param axis The axis on which this rotation will be applied.
         */
        void rotateToAngleAroundPoint(float angleRotationValue,
                                      const GeoVector4F& point,
                                      const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) =
                glm::rotate((*reinterpret_cast<const glm::vec4*>(this) - *reinterpret_cast<const glm::vec4*>(&point)),
                            glm::radians(angleRotationValue), *reinterpret_cast<const glm::vec3*>(&axis)) +
                *reinterpret_cast<const glm::vec4*>(&point);
        }

        /**
         * @brief Evaluates this GeoVector4F with another GeoVector4F to determine if all components are within a given
         * range of tolerance.
         *
         * @param other The other GeoVector4F whose components are evaluated against this GeoVector4F's components.
         * @param epsilonValue The vector determining the tolerance per component.
         * @return true if the difference between this vector and other vector falls within the tolerance set by the
         * epsilonValue vector, otherwise false.
         */
        bool epsilonEquals(const GeoVector4F& other, const GeoVector4F& epsilonValue) const noexcept
        {
            return glm::all(glm::equal(vec4Value(), other.vec4Value(), epsilonValue.vec4Value()));
        }

        /**
         * @brief Creates a new GeoVector4F instance with a uniform value of zero.
         *
         * @return A new GeoVector4F instance with all components set to zero.
         */
        static GeoVector4F zero() noexcept
        {
            return GeoVector4F::uniform(0);
        }

        /**
         * @brief Creates a new GeoVector4F instance with a uniform value of one.
         *
         * @return A new GeoVector4F instance with all components set to one.
         */
        static GeoVector4F one() noexcept
        {
            return GeoVector4F::uniform(1);
        }

        /**
         * @brief Creates a new uniform GeoVector4F based on the specified value.
         *
         * @param The value to use as the uniform value across the GeoVector4F.
         * @return a new GeoVector4F instance with all components set to the specified value.
         */
        static GeoVector4F uniform(float value) noexcept
        {
            return GeoVector4F(value, value, value, value);
        }
    };

    /**
     * @brief Calculates the product of the provided GeoVector4F and the provided scalar.
     *
     * @details
     * An example of a multiplication between a Four-dimensional vector and a scalar: \f[
     *      4
     *      \times
     *      \begin{pmatrix}
     *      8\\
     *      6\\
     *      3\\
     *      7
     *      \end{pmatrix}
     *      \rightarrow
     *      \begin{pmatrix}
     *      4\\
     *      4\\
     *      4\\
     *      4
     *      \end{pmatrix}
     *      \circ
     *      \begin{pmatrix}
     *      8\\
     *      6\\
     *      3\\
     *      7
     *      \end{pmatrix}
     *      =
     *      \begin{pmatrix}
     *      4 \times 8 \\
     *      4 \times 6 \\
     *      4 \times 3 \\
     *      4 \times 7
     *      \end{pmatrix}
     *      \rightarrow
     *      \begin{pmatrix}
     *      32\\
     *      24\\
     *      12\\
     *      28
     *      \end{pmatrix}
     * \f]
     *
     * @param lhs The scalar that gets multiplied by the GeoVector4F's components.
     * @param rhs The GeoVector4F whos components get multiplied by the scalar.
     * @return A GeoVector4F where the components consist of the product of this and the provided scalar.
     */
    inline GeoVector4F operator*(float lhs, const GeoVector4F& rhs) noexcept
    {
        return rhs * lhs;
    }
}

#endif //! NOVELRT_MATHS_GEOVECTOR4_H
