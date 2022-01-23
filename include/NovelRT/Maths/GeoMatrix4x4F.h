// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
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
        GeoVector4F x;
        GeoVector4F y;
        GeoVector4F z;
        GeoVector4F w;

        GeoMatrix4x4F() noexcept
            : x(GeoVector4F::zero()), y(GeoVector4F::zero()), z(GeoVector4F::zero()), w(GeoVector4F::zero())
        {
        }

        GeoMatrix4x4F(GeoVector4F x, GeoVector4F y, GeoVector4F z, GeoVector4F w) noexcept : x(x), y(y), z(z), w(w)
        {
        }

        inline void Translate(Maths::GeoVector3F vector)
        {
            *reinterpret_cast<glm::mat4*>(this) =
                glm::translate(*reinterpret_cast<glm::mat4*>(this), *reinterpret_cast<glm::vec3*>(&vector));
        }

        inline void Rotate(float angleInRadians, GeoVector3F rotationAngle = GeoVector3F(0.0f, 0.0f, -1.0f))
        {
            *reinterpret_cast<glm::mat4*>(this) =
                glm::rotate(*reinterpret_cast<glm::mat4*>(this), angleInRadians,
                            *reinterpret_cast<glm::vec3*>(&rotationAngle));
        }

        inline void RotateUsingDegrees(float angleInDegrees, GeoVector3F rotationAngle = GeoVector3F(0.0f, 0.0f, -1.0f))
        {
            Rotate(Utilities::DegreesToRadians(angleInDegrees), rotationAngle);
        }

        inline void Scale(GeoVector3F scaleValue)
        {
            *reinterpret_cast<glm::mat4*>(this) =
                glm::scale(*reinterpret_cast<glm::mat4*>(this), *reinterpret_cast<glm::vec3*>(&scaleValue));
        }

        inline void Scale(GeoVector2F scaleValue)
        {
            auto vec3 = GeoVector3F(scaleValue);
            vec3.z = 1.0f;
            Scale(vec3);
        }

        inline void Transpose()
        {
            *reinterpret_cast<glm::mat4*>(this) = glm::transpose(*reinterpret_cast<glm::mat4*>(this));
        }

        inline bool operator==(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) == *reinterpret_cast<const glm::mat4*>(&other);
        }

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

        static GeoMatrix4x4F getDefaultIdentity() noexcept
        {
            return GeoMatrix4x4F(glm::identity<glm::mat4>());
        }

        static GeoMatrix4x4F CreateOrthographic(float left,
                                                float right,
                                                float bottom,
                                                float top,
                                                float zNear,
                                                float zFar) noexcept
        {
            return GeoMatrix4x4F(glm::ortho(left, right, bottom, top, zNear, zFar));
        }

        static GeoMatrix4x4F CreateFromScale(float x, float y, float z) noexcept
        {
            return GeoMatrix4x4F(glm::scale(glm::vec3(x, y, z)));
        }

        static GeoMatrix4x4F CreateFromLookAt(GeoVector3F eye, GeoVector3F centre, GeoVector3F up)
        {
            return GeoMatrix4x4F(glm::lookAt(*reinterpret_cast<glm::vec3*>(&eye),
                                             *reinterpret_cast<glm::vec3*>(&centre),
                                             *reinterpret_cast<glm::vec3*>(&up)));
        }
    };
}

#endif // NOVELRT_MATHS_GEOMATRIX4_H
