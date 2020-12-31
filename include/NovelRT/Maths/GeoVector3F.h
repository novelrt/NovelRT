// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR3_H
#define NOVELRT_MATHS_GEOVECTOR3_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths
{
    class GeoVector3F
    {
        friend class Input::InteractionService;
        friend class GeoVector4F;

      private:
        GeoVector3F(glm::vec3 value) : x(value.x), y(value.y), z(value.z)
        {
        }

      public:
        float x;
        float y;
        float z;

        GeoVector3F() : x(0.0f), y(0.0f), z(0.0f)
        {
        }
        GeoVector3F(float x, float y, float z) : x(x), y(y), z(z)
        {
        }
        GeoVector3F(GeoVector2F vec2Value) : x(vec2Value.x), y(vec2Value.y), z(0.0f)
        {
        }

        inline GeoVector3F getNormalised() const noexcept
        {
            return GeoVector3F(glm::normalize(*reinterpret_cast<const glm::vec3*>(this)));
        }

        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec3*>(this));
        }

        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        inline bool operator==(const GeoVector3F& other) const
        {
            return *reinterpret_cast<const glm::vec3*>(this) == *reinterpret_cast<const glm::vec3*>(&other);
        }

        inline bool operator!=(const GeoVector3F& other) const
        {
            return *reinterpret_cast<const glm::vec3*>(this) != *reinterpret_cast<const glm::vec3*>(&other);
        }

        inline bool operator<(const GeoVector3F& other) const
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec3*>(this), *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline bool operator<=(const GeoVector3F& other) const
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec3*>(this),
                                               *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline bool operator>(const GeoVector3F& other) const
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec3*>(this),
                                             *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline bool operator>=(const GeoVector3F& other) const
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec3*>(this),
                                                  *reinterpret_cast<const glm::vec3*>(&other)));
        }

        inline GeoVector3F operator+(const GeoVector3F& other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) + *reinterpret_cast<const glm::vec3*>(&other));
        }

        inline GeoVector3F operator-(const GeoVector3F& other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&other));
        }

        inline GeoVector3F operator*(const GeoVector3F& other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) * *reinterpret_cast<const glm::vec3*>(&other));
        }

        GeoVector3F operator/(const GeoVector3F& other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) / *reinterpret_cast<const glm::vec3*>(&other));
        }

        inline GeoVector3F operator+(float other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) + other);
        }

        inline GeoVector3F operator-(float other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) - other);
        }

        inline GeoVector3F operator*(float other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) * other);
        }

        GeoVector3F operator/(float other) const
        {
            return GeoVector3F(*reinterpret_cast<const glm::vec3*>(this) / other);
        }

        inline GeoVector3F& operator+=(const GeoVector3F& other)
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) + *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        inline GeoVector3F& operator-=(const GeoVector3F& other)
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        inline GeoVector3F operator*=(const GeoVector3F& other)
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) * *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        GeoVector3F operator/=(const GeoVector3F& other)
        {
            *reinterpret_cast<glm::vec3*>(this) =
                *reinterpret_cast<const glm::vec3*>(this) / *reinterpret_cast<const glm::vec3*>(&other);
            return *this;
        }

        inline GeoVector3F operator+=(float other)
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) + other;
            return *this;
        }

        inline GeoVector3F operator-=(float other)
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) - other;
            return *this;
        }

        inline GeoVector3F operator*=(float other)
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) * other;
            return *this;
        }

        GeoVector3F operator/=(float other)
        {
            *reinterpret_cast<glm::vec3*>(this) = *reinterpret_cast<const glm::vec3*>(this) / other;
            return *this;
        }

        void rotateToAngleAroundPoint(float angleRotationValue, const GeoVector3F& point,
                                      const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept
        {
            *reinterpret_cast<glm::vec3*>(this) =
                glm::rotate((*reinterpret_cast<const glm::vec3*>(this) - *reinterpret_cast<const glm::vec3*>(&point)),
                            glm::radians(angleRotationValue), *reinterpret_cast<const glm::vec3*>(&axis)) +
                *reinterpret_cast<const glm::vec3*>(&point);
        }

        bool epsilonEquals(const GeoVector3F& other, const GeoVector3F& epsilonValue) const noexcept
        {
            return glm::all(glm::equal(*reinterpret_cast<const glm::vec3*>(this),
                                       *reinterpret_cast<const glm::vec3*>(&other),
                                       *reinterpret_cast<const glm::vec3*>(&epsilonValue)));
        }

        static const GeoVector3F zero()
        {
            return GeoVector3F::uniform(0);
        }

        static const GeoVector3F one()
        {
            return GeoVector3F::uniform(1);
        }

        static const GeoVector3F uniform(float value)
        {
            return GeoVector3F(value, value, value);
        }
    };

    inline GeoVector3F operator*(float lhs, const GeoVector3F& rhs)
    {
        return rhs * lhs;
    }
} // namespace NovelRT::Maths

#endif //! NOVELRT_MATHS_GEOVECTOR3_H
