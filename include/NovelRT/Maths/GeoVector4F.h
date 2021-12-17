// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR4_H
#define NOVELRT_MATHS_GEOVECTOR4_H

#include "GeoVector3F.h"

namespace NovelRT::Maths
{
    class GeoVector4F
    {
        friend class Input::InteractionService;
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
        float x;
        float y;
        float z;
        float w;

        /**
         * @brief Construct new GeoVector4F with X, Y, Z, and W components set to 0
         * @returns Newly constructed GeoVector4F
         */
        GeoVector4F() noexcept
        {
        }
        /**
         * @brief Construct new GeoVector4F with X, Y, Z, and W components with x, y, z, and w paramters
         * @param x Set X Component Value
         * @param y Set Y Component Value
         * @param z Set Z Component Value
         * @param w Set W Component Value
         * @returns Newly constructed GeoVector4F
         */
        GeoVector4F(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w)
        {
        }
        /**
         * @brief Construct new GeoVector4F with X and Y components set with GeoVector2F and other components set to zero
         * @param vec2Value Set X and Y Components with GeoVector2F
         * @returns Newly constructed GeoVector4F with X and Y set by GeoVector2F and other components set to zero
         */
        GeoVector4F(GeoVector2F vec2Value) noexcept : x(vec2Value.x), y(vec2Value.y), z(0.0f), w(0.0f)
        {
        }
        /**
         * @brief Construct new GeoVector4F with X and Y components set with GeoVector3F and other components set to zero
         * @param vec2Value Set X, Y, and Z Components with GeoVector3F
         * @returns Newly constructed GeoVector4F with X, Y, and Z set by GeoVector3F and other component set to zero
         */
        GeoVector4F(const GeoVector3F& vec3Value) noexcept : x(vec3Value.x), y(vec3Value.y), z(vec3Value.z), w(0.f)
        {
        }

        /**
         * @brief Compute a normalized vector of this vector
         * @returns A Unit Vector in GeoVector4F that have the length of 1
         */
        inline GeoVector4F getNormalised() const noexcept
        {
            return GeoVector4F(glm::normalize(vec4Value()));
        }

        /**
         * @brief Compute a magnitude from 0, 0, 0, 0 Coordinate Vector
         * @returns Magnitude measured from 0, 0, 0, 0 Coordinate Vector
         */
        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec4*>(this));
        }

        /**
         * @brief Compute length
         * @returns Vector Length, also known as Magnitude
         */
        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        inline bool operator==(const GeoVector4F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec4*>(this) == *reinterpret_cast<const glm::vec4*>(&other);
        }

        inline bool operator!=(const GeoVector4F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec4*>(this) != *reinterpret_cast<const glm::vec4*>(&other);
        }

        inline bool operator<(const GeoVector4F& other) const noexcept
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec4*>(this), *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline bool operator<=(const GeoVector4F& other) const noexcept
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec4*>(this),
                                               *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline bool operator>(const GeoVector4F& other) const noexcept
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec4*>(this),
                                             *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline bool operator>=(const GeoVector4F& other) const noexcept
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec4*>(this),
                                                  *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline GeoVector4F operator+(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) + *reinterpret_cast<const glm::vec4*>(&other));
        }

        inline GeoVector4F operator-(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) - *reinterpret_cast<const glm::vec4*>(&other));
        }

        inline GeoVector4F operator*(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) * *reinterpret_cast<const glm::vec4*>(&other));
        }

        GeoVector4F operator/(const GeoVector4F& other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) / *reinterpret_cast<const glm::vec4*>(&other));
        }

        inline GeoVector4F operator+(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) + other);
        }

        inline GeoVector4F operator-(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) - other);
        }

        inline GeoVector4F operator*(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) * other);
        }

        GeoVector4F operator/(float other) const noexcept
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) / other);
        }

        inline GeoVector4F& operator+=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) += *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        inline GeoVector4F& operator-=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) -= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        inline GeoVector4F operator*=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) *= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        GeoVector4F operator/=(const GeoVector4F& other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) /= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        inline GeoVector4F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) += other;
            return *this;
        }

        inline GeoVector4F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) -= other;
            return *this;
        }

        inline GeoVector4F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) *= other;
            return *this;
        }

        GeoVector4F operator/=(float other) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) /= other;
            return *this;
        }

        /**
         * @brief Rotate this vector by using another point as a reference for magnitude.
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
         * @brief Compare this vector to other vector by using epsilonValue vector as a tolerance for any deviation between the two vectors for comparison
         * @returns Return true if comparison between this vector and other vector fall within the tolerance set by epsilonValue vector, otherwise false
         */
        bool epsilonEquals(const GeoVector4F& other, const GeoVector4F& epsilonValue) const noexcept
        {
            return glm::all(glm::equal(vec4Value(), other.vec4Value(), epsilonValue.vec4Value()));
        }

        /**
         * @brief Returns a Vector with uniform component of zero
         */
        static GeoVector4F zero() noexcept
        {
            return GeoVector4F::uniform(0);
        }

        /**
         * @brief Returns a Vector with uniform component of one
         */
        static GeoVector4F one() noexcept
        {
            return GeoVector4F::uniform(1);
        }

        /**
         * @brief Returns a Vector with both x, y, z, and w components set to value
         */
        static GeoVector4F uniform(float value) noexcept
        {
            return GeoVector4F(value, value, value, value);
        }
    };

    inline GeoVector4F operator*(float lhs, const GeoVector4F& rhs) noexcept
    {
        return rhs * lhs;
    }
}

#endif //! NOVELRT_MATHS_GEOVECTOR4_H
