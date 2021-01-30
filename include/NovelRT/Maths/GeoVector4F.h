// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR4_H
#define NOVELRT_MATHS_GEOVECTOR4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths
{
    class GeoVector4F
    {
        friend class Input::InteractionService;
        friend class GeoMatrix4x4F;

    private:
        GeoVector4F(glm::vec4 value) : x(value.x), y(value.y), z(value.z), w(value.w)
        {
        }

        inline const glm::vec4& vec4Value() const
        {
            return *reinterpret_cast<const glm::vec4*>(this);
        }

        inline glm::vec4& vec4Value()
        {
            return reinterpret_cast<glm::vec4&>(*this);
        }

    public:
        float x;
        float y;
        float z;
        float w;

        GeoVector4F()
        {
        }
        GeoVector4F(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
        {
        }
        GeoVector4F(GeoVector2F vec2Value) : x(vec2Value.x), y(vec2Value.y), z(0.0f), w(0.0f)
        {
        }
        GeoVector4F(const GeoVector3F& vec3Value) : x(vec3Value.x), y(vec3Value.y), z(vec3Value.z), w(0.f)
        {
        }

        inline GeoVector4F getNormalised() const noexcept
        {
            return GeoVector4F(glm::normalize(vec4Value()));
        }

        inline float getMagnitude() const noexcept
        {
            return glm::length(*reinterpret_cast<const glm::vec4*>(this));
        }

        inline float getLength() const noexcept
        {
            return getMagnitude();
        }

        inline bool operator==(const GeoVector4F& other) const
        {
            return *reinterpret_cast<const glm::vec4*>(this) == *reinterpret_cast<const glm::vec4*>(&other);
        }

        inline bool operator!=(const GeoVector4F& other) const
        {
            return *reinterpret_cast<const glm::vec4*>(this) != *reinterpret_cast<const glm::vec4*>(&other);
        }

        inline bool operator<(const GeoVector4F& other) const
        {
            return glm::any(
                glm::lessThan(*reinterpret_cast<const glm::vec4*>(this), *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline bool operator<=(const GeoVector4F& other) const
        {
            return glm::any(glm::lessThanEqual(*reinterpret_cast<const glm::vec4*>(this),
                                               *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline bool operator>(const GeoVector4F& other) const
        {
            return glm::any(glm::greaterThan(*reinterpret_cast<const glm::vec4*>(this),
                                             *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline bool operator>=(const GeoVector4F& other) const
        {
            return glm::any(glm::greaterThanEqual(*reinterpret_cast<const glm::vec4*>(this),
                                                  *reinterpret_cast<const glm::vec4*>(&other)));
        }

        inline GeoVector4F operator+(const GeoVector4F& other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) + *reinterpret_cast<const glm::vec4*>(&other));
        }

        inline GeoVector4F operator-(const GeoVector4F& other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) - *reinterpret_cast<const glm::vec4*>(&other));
        }

        inline GeoVector4F operator*(const GeoVector4F& other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) * *reinterpret_cast<const glm::vec4*>(&other));
        }

        GeoVector4F operator/(const GeoVector4F& other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) / *reinterpret_cast<const glm::vec4*>(&other));
        }

        inline GeoVector4F operator+(float other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) + other);
        }

        inline GeoVector4F operator-(float other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) - other);
        }

        inline GeoVector4F operator*(float other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) * other);
        }

        GeoVector4F operator/(float other) const
        {
            return GeoVector4F(*reinterpret_cast<const glm::vec4*>(this) / other);
        }

        inline GeoVector4F& operator+=(const GeoVector4F& other)
        {
            *reinterpret_cast<glm::vec4*>(this) += *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        inline GeoVector4F& operator-=(const GeoVector4F& other)
        {
            *reinterpret_cast<glm::vec4*>(this) -= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        inline GeoVector4F operator*=(const GeoVector4F& other)
        {
            *reinterpret_cast<glm::vec4*>(this) *= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        GeoVector4F operator/=(const GeoVector4F& other)
        {
            *reinterpret_cast<glm::vec4*>(this) /= *reinterpret_cast<const glm::vec4*>(&other);
            return *this;
        }

        inline GeoVector4F operator+=(float other)
        {
            *reinterpret_cast<glm::vec4*>(this) += other;
            return *this;
        }

        inline GeoVector4F operator-=(float other)
        {
            *reinterpret_cast<glm::vec4*>(this) -= other;
            return *this;
        }

        inline GeoVector4F operator*=(float other)
        {
            *reinterpret_cast<glm::vec4*>(this) *= other;
            return *this;
        }

        GeoVector4F operator/=(float other)
        {
            *reinterpret_cast<glm::vec4*>(this) /= other;
            return *this;
        }

        void rotateToAngleAroundPoint(float angleRotationValue,
                                      const GeoVector4F& point,
                                      const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept
        {
            *reinterpret_cast<glm::vec4*>(this) =
                glm::rotate((*reinterpret_cast<const glm::vec4*>(this) - *reinterpret_cast<const glm::vec4*>(&point)),
                            glm::radians(angleRotationValue), *reinterpret_cast<const glm::vec3*>(&axis)) +
                *reinterpret_cast<const glm::vec4*>(&point);
        }

        bool epsilonEquals(const GeoVector4F& other, const GeoVector4F& epsilonValue) const noexcept
        {
            return glm::all(glm::equal(vec4Value(), other.vec4Value(), epsilonValue.vec4Value()));
        }

        static const GeoVector4F zero()
        {
            return GeoVector4F::uniform(0);
        }

        static const GeoVector4F one()
        {
            return GeoVector4F::uniform(1);
        }

        static const GeoVector4F uniform(float value)
        {
            return GeoVector4F(value, value, value, value);
        }
    };

    inline GeoVector4F operator*(float lhs, const GeoVector4F& rhs)
    {
        return rhs * lhs;
    }
} // namespace NovelRT::Maths

#endif //! NOVELRT_MATHS_GEOVECTOR4_H
