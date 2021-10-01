// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#include "GeoVector4F.h"

namespace NovelRT::Maths
{
    /**
     * @brief 4x4 Components Matrix, usually to represent the coordination systems
     */
    class GeoMatrix4x4F
    {
        friend class Graphics::RenderObject;
        friend class Graphics::ImageRect;
        friend class Graphics::BasicFillRect;
        friend class Graphics::TextRect;
        friend class Graphics::RenderingService;
        friend class Graphics::Camera;

    private:
        explicit GeoMatrix4x4F(glm::mat4 matrix) noexcept
            : x(*reinterpret_cast<GeoVector4F*>(&matrix[0])),
              y(*reinterpret_cast<GeoVector4F*>(&matrix[1])),
              z(*reinterpret_cast<GeoVector4F*>(&matrix[2])),
              w(*reinterpret_cast<GeoVector4F*>(&matrix[3]))
        {
        }

    public:
        GeoVector4F x;
        GeoVector4F y;
        GeoVector4F z;
        GeoVector4F w;

        /**
         * @brief Construct 4x4 Matrix with all components being set to zero
         * @returns Newly constructed GeoMatrix4x4F object
         */
        GeoMatrix4x4F() noexcept
            : x(GeoVector4F::zero()), y(GeoVector4F::zero()), z(GeoVector4F::zero()), w(GeoVector4F::zero())
        {
        }

        /**
         * @brief Construct 4x4 Matrix by providing a 4D Vector for X, Y, Z, W components of 4x4 Matrix
         * @returns Newly constructed GeoMatrix4x4F object
         */
        GeoMatrix4x4F(GeoVector4F x, GeoVector4F y, GeoVector4F z, GeoVector4F w) noexcept : x(x), y(y), z(z), w(w)
        {
        }

        /**
         * @brief Evaluates this 4x4 Matrix with another 4x4 Matrix to determine if all components matches
         * @returns Return true if all components matched, otherwise false
         */
        inline bool operator==(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) == *reinterpret_cast<const glm::mat4*>(&other);
        }

        /**
         * @brief Evaluates this 4x4 Matrix with another 4x4 Matrix to determine if any or all components doesn't match
         * @returns Return true any of the component does not match, otherwise false
         */
        inline bool operator!=(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) != *reinterpret_cast<const glm::mat4*>(&other);
        }

        inline GeoMatrix4x4F operator+(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) +
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator-(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) -
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator*(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) *
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator+=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) += *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator-=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) -= *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator*=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) *= *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator+(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) + other);
        }

        inline GeoMatrix4x4F operator-(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) - other);
        }

        inline GeoMatrix4x4F operator*(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) * other);
        }

        inline GeoMatrix4x4F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) += other;
            return *this;
        }

        inline GeoMatrix4x4F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) -= other;
            return *this;
        }

        inline GeoMatrix4x4F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) *= other;
            return *this;
        }
        /**
         * @brief Get Identity Matrix
         * @details An identity matrix that is as followed: \f[
         *      \begin{bmatrix}
         *      1 & 0 & 0 & 0\\
         *      0 & 1 & 0 & 0\\
         *      0 & 0 & 1 & 0\\
         *      0 & 0 & 0 & 1
         *      \end{bmatrix}
         * \f]
         * @returns Returns an Identity 4x4 Matrix
         */
        static GeoMatrix4x4F getDefaultIdentity() noexcept
        {
            return GeoMatrix4x4F(glm::identity<glm::mat4>());
        }
    };
} // namespace NovelRT::Maths

#endif // NOVELRT_MATHS_GEOMATRIX4_H
