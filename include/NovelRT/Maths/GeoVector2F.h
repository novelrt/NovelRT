// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR2_H
#define NOVELRT_MATHS_GEOVECTOR2_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace NovelRT::Graphics
{
    class RenderObject;
    class ImageRect;
    class BasicFillRect;
    class TextRect;
    class RenderingService;
    class Camera;
}

namespace NovelRT::Input
{
    class InteractionService;
}

namespace NovelRT::Maths
{
    class GeoVector2F
    {
        friend class Graphics::RenderObject;
        friend class Input::InteractionService;
        friend class GeoVector3F;
        friend class GeoVector4F;

    private:
        explicit GeoVector2F(glm::vec2 value) noexcept : x(value.x), y(value.y)
        {
        }

    public:
        float x;
        float y;

        /**
         * @brief Construct new GeoVector2F with X and Y components set to 0
         * @returns Newly constructed GeoVector2F
         */
        GeoVector2F() noexcept : x(0.0f), y(0.0f)
        {
        }

        /**
         * @brief Construct new GeoVector2F with X and Y components with x and y paramters
         * @param x Set X Component Value
         * @param y Set Y Component Value
         * @returns Newly constructed GeoVector2F
         */
        GeoVector2F(float x, float y) noexcept : x(x), y(y)
        {
        }

        /**
         * @brief Compute a normalized vector of this vector
         * @returns A Unit Vector in GeoVector2F that have the length of 1
         */
        inline GeoVector2F getNormalised() const noexcept
        {
            return GeoVector2F(glm::normalize(*reinterpret_cast<const glm::vec2*>(this)));
        }

        /**
         * @brief Compute a magnitude from 0, 0 Coordinate Vector
         * @returns Magnitude measured from 0, 0 Coordinate Vector
         */
        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec2*>(this));
        }

        /**
         * @brief Compute length
         * @returns Vector Length, also known as Magnitude
         */
        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        inline bool operator==(GeoVector2F other) const noexcept
        {
            return *reinterpret_cast<const glm::vec2*>(this) == *reinterpret_cast<const glm::vec2*>(&other);
        }

        inline bool operator!=(GeoVector2F other) const noexcept
        {
            return *reinterpret_cast<const glm::vec2*>(this) != *reinterpret_cast<const glm::vec2*>(&other);
        }

        inline bool operator<(GeoVector2F other) const noexcept
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec2*>(this), *reinterpret_cast<const glm::vec2*>(&other)));
        }

        inline bool operator<=(GeoVector2F other) const noexcept
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec2*>(this),
                                               *reinterpret_cast<const glm::vec2*>(&other)));
        }

        inline bool operator>(GeoVector2F other) const noexcept
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec2*>(this),
                                             *reinterpret_cast<const glm::vec2*>(&other)));
        }

        inline bool operator>=(GeoVector2F other) const noexcept
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec2*>(this),
                                                  *reinterpret_cast<const glm::vec2*>(&other)));
        }

        inline GeoVector2F operator+(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) + *reinterpret_cast<const glm::vec2*>(&other));
        }

        inline GeoVector2F operator-(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) - *reinterpret_cast<const glm::vec2*>(&other));
        }

        inline GeoVector2F operator*(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) * *reinterpret_cast<const glm::vec2*>(&other));
        }

        GeoVector2F operator/(GeoVector2F other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) / *reinterpret_cast<const glm::vec2*>(&other));
        }

        inline GeoVector2F operator+(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) + other);
        }

        inline GeoVector2F operator-(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) - other);
        }

        inline GeoVector2F operator*(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) * other);
        }

        GeoVector2F operator/(float other) const noexcept
        {
            return GeoVector2F(*reinterpret_cast<const glm::vec2*>(this) / other);
        }

        inline GeoVector2F& operator+=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) + *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        inline GeoVector2F& operator-=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) - *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        inline GeoVector2F operator*=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) * *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        GeoVector2F operator/=(GeoVector2F other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) =
                *reinterpret_cast<const glm::vec2*>(this) / *reinterpret_cast<const glm::vec2*>(&other);
            return *this;
        }

        inline GeoVector2F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) + other;
            return *this;
        }

        inline GeoVector2F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) - other;
            return *this;
        }

        inline GeoVector2F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) * other;
            return *this;
        }

        inline GeoVector2F operator/=(float other) noexcept
        {
            *reinterpret_cast<glm::vec2*>(this) = *reinterpret_cast<const glm::vec2*>(this) / other;
            return *this;
        }
        /**
         * @brief Rotate this vector by using another point as a reference for magnitude.
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
         * @brief Compare this vector to other vector by using epsilonValue vector as a tolerance for any deviation between the two vectors for comparison
         * @returns Return true if comparison between this vector and other vector fall within the tolerance set by epsilonValue vector, otherwise false
         */
        bool epsilonEquals(GeoVector2F other, GeoVector2F epsilonValue) const noexcept
        {
            return glm::all(glm::equal(*reinterpret_cast<const glm::vec2*>(this),
                                       *reinterpret_cast<const glm::vec2*>(&other),
                                       *reinterpret_cast<const glm::vec2*>(&epsilonValue)));
        }

        /**
         * @brief Returns a Vector with uniform component of zero
         */
        static GeoVector2F zero() noexcept
        {
            return GeoVector2F::uniform(0);
        }

        /**
         * @brief Returns a Vector with uniform component of one
         */
        static GeoVector2F one() noexcept
        {
            return GeoVector2F::uniform(1);
        }

        /**
         * @brief Returns a Vector with both x and y components set to value
         */
        static GeoVector2F uniform(float value) noexcept
        {
            return GeoVector2F(value, value);
        }
    };

    inline GeoVector2F operator*(float lhs, GeoVector2F rhs) noexcept
    {
        return rhs * lhs;
    }

}

#endif //! NOVELRT_MATHS_GEOVECTOR2_H
