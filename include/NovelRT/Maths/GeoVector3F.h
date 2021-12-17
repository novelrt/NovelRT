// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR3_H
#define NOVELRT_MATHS_GEOVECTOR3_H

#include "GeoVector2F.h"

namespace NovelRT::Maths
{
    class GeoVector3F
    {
        friend class Input::InteractionService;
        friend class GeoVector4F;

    private:
        GeoVector3F(glm::vec3 value) noexcept : x(value.x), y(value.y), z(value.z)
        {
        }

    public:
        float x;
        float y;
        float z;

        /**
         * @brief Construct new GeoVector3F with X, Y, and Z components set to 0
         * @returns Newly constructed GeoVector3F
         */
        GeoVector3F() noexcept : x(0.0f), y(0.0f), z(0.0f)
        {
        }
        /**
         * @brief Construct new GeoVector3F with X, Y, and Z components with x, y and z paramters
         * @param x Set X Component Value
         * @param y Set Y Component Value
         * @param z Set Z Component Value
         * @returns Newly constructed GeoVector3F
         */
        GeoVector3F(float x, float y, float z) noexcept : x(x), y(y), z(z)
        {
        }
        /**
         * @brief Construct new GeoVector3F with X and Y components set with GeoVector2F and other component set to zero
         * @param vec2Value Set X and Y Components with GeoVector2F
         * @returns Newly constructed GeoVector3F with X and Y set by GeoVector2F and other component set to zero
         */
        GeoVector3F(GeoVector2F vec2Value) noexcept : x(vec2Value.x), y(vec2Value.y), z(0.0f)
        {
        }

        /**
         * @brief Compute a normalized vector of this vector
         * @returns A Unit Vector in GeoVector3F that have the length of 1
         */
        inline GeoVector3F getNormalised() const noexcept
        {
            return GeoVector3F(glm::normalize(*reinterpret_cast<const glm::vec3*>(this)));
        }

        /**
         * @brief Compute a magnitude from 0, 0, 0 Coordinate Vector
         * @returns Magnitude measured from 0, 0, 0 Coordinate Vector
         */
        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec3*>(this));
        }

        /**
         * @brief Compute length
         * @returns Vector Length, also known as Magnitude
         */
        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        inline bool operator==(const GeoVector3F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec3*>(this) == *reinterpret_cast<const glm::vec3*>(&other);
        }

        inline bool operator!=(const GeoVector3F& other) const noexcept
        {
            return *reinterpret_cast<const glm::vec3*>(this) != *reinterpret_cast<const glm::vec3*>(&other);
        }

        inline bool operator<(const GeoVector3F& other) const noexcept
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec3*>(this), *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline bool operator<=(const GeoVector3F& other) const noexcept
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec3*>(this),
                                               *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline bool operator>(const GeoVector3F& other) const noexcept
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec3*>(this),
                                             *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline bool operator>=(const GeoVector3F& other) const noexcept
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec3*>(this),
                                                  *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline GeoVector3F operator+(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) + *reinterpret_cast<const glm::vec3*>(&other));
        }

        inline GeoVector3F operator-(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&other));
        }

        inline GeoVector3F operator*(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) * *reinterpret_cast<const glm::vec3*>(&other));
        }

        GeoVector3F operator/(const GeoVector3F& other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) / *reinterpret_cast<const glm::vec3*>(&other));
        }

        inline GeoVector3F operator+(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) + other);
        }

        inline GeoVector3F operator-(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) - other);
        }

        inline GeoVector3F operator*(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) * other);
        }

        GeoVector3F operator/(float other) const noexcept
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) / other);
        }

        inline GeoVector3F& operator+=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) + *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        inline GeoVector3F& operator-=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        inline GeoVector3F operator*=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) * *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        GeoVector3F operator/=(const GeoVector3F& other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) / *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        inline GeoVector3F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) + other;
            return *this;
        }

        inline GeoVector3F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) - other;
            return *this;
        }

        inline GeoVector3F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) * other;
            return *this;
        }

        GeoVector3F operator/=(float other) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) / other;
            return *this;
        }

        /**
         * @brief Rotate this vector by using another point as a reference for magnitude.
         */
        void rotateToAngleAroundPoint(float angleRotationValue,
                                      const GeoVector3F& point,
                                      const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                glm::rotate((*reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&point)),
                            glm::radians(angleRotationValue), *reinterpret_cast<const glm::vec3*>(&axis)) +
                *reinterpret_cast<const glm::vec3*>(&point);
        }
        
        /**
         * @brief Compare this vector to other vector by using epsilonValue vector as a tolerance for any deviation between the two vectors for comparison
         * @returns Return true if comparison between this vector and other vector fall within the tolerance set by epsilonValue vector, otherwise false
         */
        bool epsilonEquals(const GeoVector3F& other, const GeoVector3F& epsilonValue) const noexcept
        {
            return glm::all(glm::equal(*reinterpret_cast<const glm::vec3*>(this),
                                       *reinterpret_cast<const glm::vec3*>(&other),
                                       *reinterpret_cast<const glm::vec3*>(&epsilonValue)));
        }

        /**
         * @brief Returns a Vector with uniform component of zero
         */
        static GeoVector3F zero() noexcept
        {
            return GeoVector3F::uniform(0);
        }

        /**
         * @brief Returns a Vector with uniform component of one
         */
        static GeoVector3F one() noexcept
        {
            return GeoVector3F::uniform(1);
        }

        /**
         * @brief Returns a Vector with both x, y, and z components set to value
         */
        static GeoVector3F uniform(float value) noexcept
        {
            return GeoVector3F(value, value, value);
        }
    };

    inline GeoVector3F operator*(float lhs, const GeoVector3F& rhs) noexcept
    {
        return rhs * lhs;
    }
}

#endif //! NOVELRT_MATHS_GEOVECTOR3_H
