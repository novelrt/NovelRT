// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief A 4x4 float-based Matrix.
     */
    class GeoMatrix4x4F
    {
    private:
        explicit GeoMatrix4x4F(glm::mat4 matrix) noexcept
            : x(*reinterpret_cast<GeoVector4F*>(&matrix[0])),
              y(*reinterpret_cast<GeoVector4F*>(&matrix[1])),
              z(*reinterpret_cast<GeoVector4F*>(&matrix[2])),
              w(*reinterpret_cast<GeoVector4F*>(&matrix[3]))
        {
        }

    public:
        /**
         * @brief The first row in the matrix.
         */
        GeoVector4F x;
        /**
         * @brief The second row in the matrix.
         */
        GeoVector4F y;
        /**
         * @brief The third row in the matrix.
         */
        GeoVector4F z;
        /**
         * @brief The fourth row in the matrix.
         */
        GeoVector4F w;

        /**
         * @brief Constructs a 4x4 Matrix with all components being set to zero.
         *
         * @return The newly instantiated GeoMatrix4x4F object.
         */
        [[nodiscard]] GeoMatrix4x4F() noexcept
            : x(GeoVector4F::Zero()), y(GeoVector4F::Zero()), z(GeoVector4F::Zero()), w(GeoVector4F::Zero())
        {
        }

        /**
         * @brief Constructs a 4x4 Matrix based on the provided X, Y, Z, W components.
         *
         * @param x The first row in the matrix.
         * @param y The second row in the matrix.
         * @param z The third row in the matrix.
         * @param w The fourth row in the matrix.
         * @return The newly instantiated GeoMatrix4x4F object.
         */
        [[nodiscard]] GeoMatrix4x4F(GeoVector4F x, GeoVector4F y, GeoVector4F z, GeoVector4F w) noexcept
            : x(x), y(y), z(z), w(w)
        {
        }

        /**
         * @brief Moves the matrix by the translation vector.
         *
         * @param vector The direction and distance the matrix should be moved by.
         */
        inline void Translate(Maths::GeoVector3F vector)
        {
            *reinterpret_cast<glm::mat4*>(this) = glm::translate(*reinterpret_cast<glm::mat4*>(this),
                                                                 NovelRT::Utilities::Misc::BitCast<glm::vec3>(vector));
        }

        /**
         * @brief Rotates the matrix by a given angle around a set axis.
         *
         * @param angleInRadians The angle to rotate by in radians.
         * @param rotationAngle The axis to rotate on. If none is provided, it will rotate clockwise around the Z axis.
         */
        inline void Rotate(float angleInRadians, GeoVector3F rotationAngle = GeoVector3F(0.0f, 0.0f, -1.0f))
        {
            *reinterpret_cast<glm::mat4*>(this) =
                glm::rotate(*reinterpret_cast<glm::mat4*>(this), angleInRadians,
                            NovelRT::Utilities::Misc::BitCast<glm::vec3>(rotationAngle));
        }

        /**
         * @brief Rotates the matrix by a given angle around a set axis.
         *
         * @param angleInDegrees The angle to rotate by in degrees.
         * @param rotationAngle The axis to rotate on. If none is provided, it will rotate clockwise around the Z axis.
         */
        inline void RotateUsingDegrees(float angleInDegrees, GeoVector3F rotationAngle = GeoVector3F(0.0f, 0.0f, -1.0f))
        {
            Rotate(Utilities::DegreesToRadians(angleInDegrees), rotationAngle);
        }

        /**
         * @brief Scales the matrix by the given vector.
         *
         * @param scaleValue The vector to scale by.
         */
        inline void Scale(GeoVector3F scaleValue)
        {
            *reinterpret_cast<glm::mat4*>(this) = glm::scale(*reinterpret_cast<glm::mat4*>(this),
                                                             NovelRT::Utilities::Misc::BitCast<glm::vec3>(scaleValue));
        }

        /**
         * @brief Scales the matrix by the given vector.
         *
         * @param scaleValue The vector to scale by.
         */
        inline void Scale(GeoVector2F scaleValue)
        {
            auto vec3 = GeoVector3F(scaleValue);
            vec3.z = 1.0f;
            Scale(vec3);
        }

        /**
         * @brief Flips the matrix alongside its descending diagonal.
         *
         * @details
         * An example of transposing a matrix: \f[
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      =
         *      \begin{bmatrix}
         *      1 & 2 & 3 & 4\\
         *      7 & 1 & 5 & 6\\
         *      6 & 4 & 1 & 7\\
         *      5 & 3 & 2 & 1
         *      \end{bmatrix}
         * \f]
         */
        inline void Transpose()
        {
            *reinterpret_cast<glm::mat4*>(this) = glm::transpose(*reinterpret_cast<glm::mat4*>(this));
        }

        /**
         * @brief Evaluates this GeoMatrix4x4F with another GeoMatrix4x4F to determine if all components match.
         *
         * @param other The other GeoMatrix4x4F to evaluate against.
         * @return true if all components matched, otherwise false.
         */
        [[nodiscard]] inline bool operator==(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) == NovelRT::Utilities::Misc::BitCast<glm::mat4>(other);
        }

        /**
         * @brief Evaluates this GeoMatrix4x4F with another GeoMatrix4x4F to determine if any or all components do not
         * match.
         *
         * @param other The other GeoMatrix4x4F to evaluate against.
         * @return true if any of the components do not match, otherwise false.
         */
        [[nodiscard]] inline bool operator!=(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) != NovelRT::Utilities::Misc::BitCast<glm::mat4>(other);
        }

        /**
         * @brief Calculates the entrywise sum of this GeoMatrix4x4F and another GeoMatrix4x4F.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise sum: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      +
         *      \begin{bmatrix}
         *      4 & 7 & 2 & 5\\
         *      5 & 1 & 8 & 4\\
         *      8 & 3 & 2 & 2\\
         *      6 & 7 & 6 & 8
         *      \end{bmatrix}
         *      &=
         *      \begin{bmatrix}
         *      1+4 & 7+7 & 6+2 & 5+5\\
         *      2+5 & 1+1 & 4+8 & 3+4\\
         *      3+8 & 5+3 & 1+2 & 2+2\\
         *      4+6 & 6+7 & 7+6 & 1+8
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      5 & 14 & 8 & 10\\
         *      7 & 2 & 12 & 7\\
         *      11 & 8 & 3 & 4\\
         *      10 & 13 & 13 & 9
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other matrix whose components get added together with this matrix.
         * @return A matrix where the components consist of the entrywise sum of this GeoMatrix4x4F and another
         * GeoMatrix4x4F.
         */
        [[nodiscard]] inline GeoMatrix4x4F operator+(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) +
                                 NovelRT::Utilities::Misc::BitCast<glm::mat4>(other));
        }

        /**
         * @brief Calculates the entrywise difference of this GeoMatrix4x4F and another GeoMatrix4x4F.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise difference: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      -
         *      \begin{bmatrix}
         *      4 & 7 & 2 & 5\\
         *      5 & 1 & 8 & 4\\
         *      8 & 3 & 2 & 2\\
         *      6 & 7 & 6 & 8
         *      \end{bmatrix}
         *      &=
         *      \begin{bmatrix}
         *      1-4 & 7-7 & 6-2 & 5-5\\
         *      2-5 & 1-1 & 4-8 & 3-4\\
         *      3-8 & 5-3 & 1-2 & 2-2\\
         *      4-6 & 6-7 & 7-6 & 1-8
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      -3 & 0 & 4 & 0\\
         *      -3 & 0 & -4 & 1\\
         *      -5 & 2 & -1 & 0\\
         *      -2 & -1 & 1 & -7
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other matrix whose components get subtracted from this matrix.
         * @return A matrix where the components consist of the entrywise difference of this GeoMatrix4x4F and another
         * GeoMatrix4x4F.
         */
        [[nodiscard]] inline GeoMatrix4x4F operator-(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) -
                                 NovelRT::Utilities::Misc::BitCast<glm::mat4>(other));
        }

        /**
         * @brief Calculates the product of this GeoMatrix4x4F and another GeoMatrix4x4F.
         *
         * @details
         * An example of a matrix that would be constructed from multiplying two matrices: \f{align*}{
         *      \begin{bmatrix}
         *      4 & 7 & 2 & 5\\
         *      5 & 1 & 8 & 4\\
         *      8 & 3 & 2 & 2\\
         *      6 & 7 & 6 & 8
         *      \end{bmatrix}
         *      \cdot
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      &=
         *      \begin{bmatrix}
         *      1*4+7*5+6*8+5*6 & 1*7+7*1+6*3+5*7 & 1*2+7*8+6*2+5*6 & 1*5+7*4+6*2+5*8\\
         *      2*4+1*5+4*8+3*6 & 2*7+1*1+4*3+3*7 & 2*2+1*8+4*2+3*6 & 2*5+1*4+4*2+3*8\\
         *      3*4+5*5+1*8+2*6 & 3*7+5*1+1*3+2*7 & 3*2+5*8+1*2+2*6 & 3*5+5*4+1*2+2*8\\
         *      4*4+6*5+7*8+1*6 & 4*7+6*1+7*3+1*7 & 4*2+6*8+7*2+1*6 & 4*5+6*4+7*2+1*8
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      117 & 67 & 100 & 85\\
         *      63 & 48 & 38 & 46\\
         *      57 & 43 & 60 & 53\\
         *      108 & 62 & 76 & 66
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other matrix whose columns are multiplied and summed up by this matrix's rows.
         * @return A matrix product where the components consist of the sum of the products of this GeoMatrix4x4F's rows
         * and another GeoMatrix4x4F's columns.
         */
        [[nodiscard]] inline GeoMatrix4x4F operator*(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) *
                                 NovelRT::Utilities::Misc::BitCast<glm::mat4>(other));
        }

        /**
         * @brief Calculates the entrywise sum of this GeoMatrix4x4F and another GeoMatrix4x4F and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise sum: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      +
         *      \begin{bmatrix}
         *      4 & 7 & 2 & 5\\
         *      5 & 1 & 8 & 4\\
         *      8 & 3 & 2 & 2\\
         *      6 & 7 & 6 & 8
         *      \end{bmatrix}
         *      &=
         *      \begin{bmatrix}
         *      1+4 & 7+7 & 6+2 & 5+5\\
         *      2+5 & 1+1 & 4+8 & 3+4\\
         *      3+8 & 5+3 & 1+2 & 2+2\\
         *      4+6 & 6+7 & 7+6 & 1+8
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      5 & 14 & 8 & 10\\
         *      7 & 2 & 12 & 7\\
         *      11 & 8 & 3 & 4\\
         *      10 & 13 & 13 & 9
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other matrix whose components get added together with this matrix.
         * @return This matrix where the components consist of the entrywise sum of this GeoMatrix4x4F and another
         * GeoMatrix4x4F.
         */
        inline GeoMatrix4x4F operator+=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) += NovelRT::Utilities::Misc::BitCast<glm::mat4>(other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoMatrix4x4F and another GeoMatrix4x4F and overwrites
         * this instance with the result.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise difference: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      -
         *      \begin{bmatrix}
         *      4 & 7 & 2 & 5\\
         *      5 & 1 & 8 & 4\\
         *      8 & 3 & 2 & 2\\
         *      6 & 7 & 6 & 8
         *      \end{bmatrix}
         *      &=
         *      \begin{bmatrix}
         *      1-4 & 7-7 & 6-2 & 5-5\\
         *      2-5 & 1-1 & 4-8 & 3-4\\
         *      3-8 & 5-3 & 1-2 & 2-2\\
         *      4-6 & 6-7 & 7-6 & 1-8
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      -3 & 0 & 4 & 0\\
         *      -3 & 0 & -4 & 1\\
         *      -5 & 2 & -1 & 0\\
         *      -2 & -1 & 1 & -7
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other matrix whose components get subtracted from this matrix.
         * @return This matrix where the components consist of the entrywise difference of this GeoMatrix4x4F and
         * another GeoMatrix4x4F.
         */
        inline GeoMatrix4x4F operator-=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) -= NovelRT::Utilities::Misc::BitCast<glm::mat4>(other);
            return *this;
        }

        /**
         * @brief Calculate the product of this GeoMatrix4x4F and another GeoMatrix4x4F and overwrites this instance
         * with the result.
         *
         * @details
         * An example of a matrix that would be constructed from multiplying two matrices: \f{align*}{
         *      \begin{bmatrix}
         *      4 & 7 & 2 & 5\\
         *      5 & 1 & 8 & 4\\
         *      8 & 3 & 2 & 2\\
         *      6 & 7 & 6 & 8
         *      \end{bmatrix}
         *      \cdot
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      &=
         *      \begin{bmatrix}
         *      1*4+7*5+6*8+5*6 & 1*7+7*1+6*3+5*7 & 1*2+7*8+6*2+5*6 & 1*5+7*4+6*2+5*8\\
         *      2*4+1*5+4*8+3*6 & 2*7+1*1+4*3+3*7 & 2*2+1*8+4*2+3*6 & 2*5+1*4+4*2+3*8\\
         *      3*4+5*5+1*8+2*6 & 3*7+5*1+1*3+2*7 & 3*2+5*8+1*2+2*6 & 3*5+5*4+1*2+2*8\\
         *      4*4+6*5+7*8+1*6 & 4*7+6*1+7*3+1*7 & 4*2+6*8+7*2+1*6 & 4*5+6*4+7*2+1*8
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      117 & 67 & 100 & 85\\
         *      63 & 48 & 38 & 46\\
         *      57 & 43 & 60 & 53\\
         *      108 & 62 & 76 & 66
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other matrix whose columns are multiplied and summed up by this matrix's rows.
         * @return This matrix where the components consist of the sum of the products of this GeoMatrix4x4F's rows and
         * another GeoMatrix4x4F's columns.
         */
        inline GeoMatrix4x4F operator*=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) *= NovelRT::Utilities::Misc::BitCast<glm::mat4>(other);
            return *this;
        }

        /**
         * @brief Calculates the entrywise sum of this GeoMatrix4x4F and the provided scalar.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise sum with a scalar: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      + 6
         *      &\rightarrow
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      +
         *      \begin{bmatrix}
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      1+6 & 7+6 & 6+6 & 5+6\\
         *      2+6 & 1+6 & 4+6 & 3+6\\
         *      3+6 & 5+6 & 1+6 & 2+6\\
         *      4+6 & 6+6 & 7+6 & 1+6\\
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      7 & 13 & 12 & 11\\
         *      8 & 7 & 10 & 9\\
         *      9 & 11 & 7 & 8\\
         *      10& 12 & 13 & 7
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other scalar that gets added together with this matrix.
         * @return A matrix where the components consist of the entrywise sum of this GeoMatrix4x4F and the provided
         * scalar.
         */
        [[nodiscard]] inline GeoMatrix4x4F operator+(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) + other);
        }

        /**
         * @brief Calculates the entrywise difference of this GeoMatrix4x4F and the provided scalar.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise difference with a scalar: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      -6
         *      &\rightarrow
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      -
         *      \begin{bmatrix}
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      1-6 & 7-6 & 6-6 & 5-6\\
         *      2-6 & 1-6 & 4-6 & 3-6\\
         *      3-6 & 5-6 & 1-6 & 2-6\\
         *      4-6 & 6-6 & 7-6 & 1-6\\
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      -5 & 1 & 0 & -1\\
         *      -4 & -5 & -2 & -3\\
         *      -3 & -1 & -5 & -4\\
         *      -2 & 0 & 1 & -5\\
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other scalar that gets subtracted from this matrix.
         * @return A matrix where the components consist of the entrywise difference of this GeoMatrix4x4F and the
         * provided scalar.
         */
        [[nodiscard]] inline GeoMatrix4x4F operator-(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) - other);
        }

        /**
         * @brief Calculates the product of this GeoMatrix4x4F and the provided scalar.
         *
         * @details
         * An example of a matrix that would be constructed from multiplying a matrix by a scalar: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      \cdot 6
         *      &\rightarrow
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      \cdot
         *      \begin{bmatrix}
         *      6 & 0 & 0 & 0\\
         *      0 & 6 & 0 & 0\\
         *      0 & 0 & 6 & 0\\
         *      0 & 0 & 0 & 6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      1*6+7*0+6*0+5*0 & 1*0+7*6+6*0+5*0 & 1*0+7*0+6*6+5*0 & 1*0+7*0+6*0+5*6\\
         *      2*6+1*0+4*0+3*0 & 2*0+1*6+4*0+3*0 & 2*0+1*0+4*6+3*0 & 2*0+1*0+4*0+3*6\\
         *      3*6+5*0+1*0+2*0 & 3*0+5*6+1*0+2*0 & 3*0+5*0+1*6+2*0 & 3*0+5*0+1*0+2*6\\
         *      4*6+6*0+7*0+1*0 & 4*0+6*6+7*0+1*0 & 4*0+6*0+7*6+1*0 & 4*0+6*0+7*0+1*6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      6 & 42 & 36 & 30\\
         *      12 & 6 & 24 & 18\\
         *      18 & 30 & 6 & 12\\
         *      24 & 36 & 42 & 6
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other scalar that gets multiplied by this matrix.
         * @return a matrix where the components consist of the product of this GeoMatrix4x4F and the provided scalar.
         */
        [[nodiscard]] inline GeoMatrix4x4F operator*(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) * other);
        }

        /**
         * @brief Calculates the entrywise sum of this GeoMatrix4x4F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise sum with a scalar: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      + 6
         *      &\rightarrow
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      +
         *      \begin{bmatrix}
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      1+6 & 7+6 & 6+6 & 5+6\\
         *      2+6 & 1+6 & 4+6 & 3+6\\
         *      3+6 & 5+6 & 1+6 & 2+6\\
         *      4+6 & 6+6 & 7+6 & 1+6\\
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      7 & 13 & 12 & 11\\
         *      8 & 7 & 10 & 9\\
         *      9 & 11 & 7 & 8\\
         *      10& 12 & 13 & 7
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other scalar that gets added together with this matrix.
         * @return This matrix where the components consist of the entrywise sum of this GeoMatrix4x4F and the provided
         * scalar.
         */
        inline GeoMatrix4x4F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) += other;
            return *this;
        }

        /**
         * @brief Calculates the entrywise difference of this GeoMatrix4x4F and the provided scalar and overwrites this
         * instance with the result.
         *
         * @details
         * An example of a matrix that would be constructed from an entrywise difference with a scalar: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      -6
         *      &\rightarrow
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      -
         *      \begin{bmatrix}
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6\\
         *      6 & 6 & 6 & 6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      1-6 & 7-6 & 6-6 & 5-6\\
         *      2-6 & 1-6 & 4-6 & 3-6\\
         *      3-6 & 5-6 & 1-6 & 2-6\\
         *      4-6 & 6-6 & 7-6 & 1-6\\
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      -5 & 1 & 0 & -1\\
         *      -4 & -5 & -2 & -3\\
         *      -3 & -1 & -5 & -4\\
         *      -2 & 0 & 1 & -5\\
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other scalar that gets subtracted from this matrix.
         * @return This matrix where the components consist of the entrywise difference of this GeoMatrix4x4F and the
         * provided scalar.
         */
        inline GeoMatrix4x4F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) -= other;
            return *this;
        }

        /**
         * @brief Calculates the product of this GeoMatrix4x4F and the provided scalar and overwrites this instance with
         * the result.
         *
         * @details
         * An example of a matrix that would be constructed from multiplying a matrix by a scalar: \f{align*}{
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      \cdot 6
         *      &\rightarrow
         *      \begin{bmatrix}
         *      1 & 7 & 6 & 5\\
         *      2 & 1 & 4 & 3\\
         *      3 & 5 & 1 & 2\\
         *      4 & 6 & 7 & 1
         *      \end{bmatrix}
         *      \cdot
         *      \begin{bmatrix}
         *      6 & 0 & 0 & 0\\
         *      0 & 6 & 0 & 0\\
         *      0 & 0 & 6 & 0\\
         *      0 & 0 & 0 & 6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      1*6+7*0+6*0+5*0 & 1*0+7*6+6*0+5*0 & 1*0+7*0+6*6+5*0 & 1*0+7*0+6*0+5*6\\
         *      2*6+1*0+4*0+3*0 & 2*0+1*6+4*0+3*0 & 2*0+1*0+4*6+3*0 & 2*0+1*0+4*0+3*6\\
         *      3*6+5*0+1*0+2*0 & 3*0+5*6+1*0+2*0 & 3*0+5*0+1*6+2*0 & 3*0+5*0+1*0+2*6\\
         *      4*6+6*0+7*0+1*0 & 4*0+6*6+7*0+1*0 & 4*0+6*0+7*6+1*0 & 4*0+6*0+7*0+1*6
         *      \end{bmatrix}\\
         *      &=
         *      \begin{bmatrix}
         *      6 & 42 & 36 & 30\\
         *      12 & 6 & 24 & 18\\
         *      18 & 30 & 6 & 12\\
         *      24 & 36 & 42 & 6
         *      \end{bmatrix}
         * \f}
         *
         * @param other The other scalar that gets multiplied by this matrix.
         * @return This matrix where the components consist of the product of this GeoMatrix4x4F and the provided
         * scalar.
         */
        inline GeoMatrix4x4F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) *= other;
            return *this;
        }

        /**
         * @brief Get an identity matrix, with it´s descending diagonals set to 1.
         *
         * @details
         * An identity matrix that is as followed: \f[
         *      \begin{bmatrix}
         *      1 & 0 & 0 & 0\\
         *      0 & 1 & 0 & 0\\
         *      0 & 0 & 1 & 0\\
         *      0 & 0 & 0 & 1
         *      \end{bmatrix}
         * \f]
         *
         * @return An Identity GeoMatrix4x4F.
         */
        [[nodiscard]] static GeoMatrix4x4F GetDefaultIdentity() noexcept
        {
            return GeoMatrix4x4F(glm::identity<glm::mat4>());
        }

        /**
         * @brief Creates a matrix for projecting a three-dimensional space onto a plane.
         *
         * @param left Farthest left on the x-axis.
         * @param right Farthest right on the x-axis.
         * @param bottom Farthest down on the y-axis.
         * @param top Farthest up on the y-axis.
         * @param zNear Distance to the near clipping plane along the -Z axis.
         * @param zFar Distance to the far clipping plane along the -Z axis.
         * @return A projection GeoMatrix4x4F for projecting a three-dimensional space onto a plane.
         */
        [[nodiscard]] static GeoMatrix4x4F CreateOrthographic(float left,
                                                              float right,
                                                              float bottom,
                                                              float top,
                                                              float zNear,
                                                              float zFar) noexcept
        {
            return GeoMatrix4x4F(glm::ortho(left, right, bottom, top, zNear, zFar));
        }

        /**
         * @brief Creates a matrix with the given scale components.
         *
         * @details
         * The scale components are placed in the decending diagonal of the matrix: \f[
         *      \begin{bmatrix}
         *      x & 0 & 0 & 0\\
         *      0 & y & 0 & 0\\
         *      0 & 0 & z & 0\\
         *      0 & 0 & 0 & 1
         *      \end{bmatrix}
         * \f]
         *
         * @param x The scale component over the X axis.
         * @param y The scale component over the Y axis.
         * @param z The scale component over the Z axis.
         * @return A matrix with scale components applied.
         */
        [[nodiscard]] static GeoMatrix4x4F CreateFromScale(float x, float y, float z) noexcept
        {
            return GeoMatrix4x4F(glm::scale(glm::vec3(x, y, z)));
        }

        /**
         * @brief Creates a matrix for observing a point in space from a given location.
         *
         * @param eye The position of the observer.
         * @param centre The position of the reference point the observer should look towards.
         * @param up Specifies the direction of the up vector of the observer.
         * @return A view matrix looking towards a reference point from the given eye position.
         */
        [[nodiscard]] static GeoMatrix4x4F CreateFromLookAt(GeoVector3F eye, GeoVector3F centre, GeoVector3F up)
        {
            return GeoMatrix4x4F(glm::lookAt(NovelRT::Utilities::Misc::BitCast<glm::vec3>(eye),
                                             NovelRT::Utilities::Misc::BitCast<glm::vec3>(centre),
                                             NovelRT::Utilities::Misc::BitCast<glm::vec3>(up)));
        }
    };
}

#endif // NOVELRT_MATHS_GEOMATRIX4_H
