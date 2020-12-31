// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths
{

    class GeoMatrix4x4F
    {
        friend class Graphics::RenderObject;
        friend class Graphics::ImageRect;
        friend class Graphics::BasicFillRect;
        friend class Graphics::TextRect;
        friend class Graphics::RenderingService;
        friend class Graphics::Camera;

      private:
        explicit GeoMatrix4x4F(glm::mat4 matrix)
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

        GeoMatrix4x4F() : x(GeoVector4F::zero()), y(GeoVector4F::zero()), z(GeoVector4F::zero()), w(GeoVector4F::zero())
        {
        }

        GeoMatrix4x4F(GeoVector4F x, GeoVector4F y, GeoVector4F z, GeoVector4F w) : x(x), y(y), z(z), w(w)
        {
        }

        inline bool operator==(GeoMatrix4x4F other) const
        {
            return *reinterpret_cast<const glm::mat4*>(this) == *reinterpret_cast<const glm::mat4*>(&other);
        }

        inline bool operator!=(GeoMatrix4x4F other) const
        {
            return *reinterpret_cast<const glm::mat4*>(this) != *reinterpret_cast<const glm::mat4*>(&other);
        }

        inline GeoMatrix4x4F operator+(GeoMatrix4x4F other) const
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) +
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator-(GeoMatrix4x4F other) const
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) -
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator*(GeoMatrix4x4F other) const
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) *
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator+=(GeoMatrix4x4F other)
        {
            *reinterpret_cast<glm::mat4*>(this) += *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator-=(GeoMatrix4x4F other)
        {
            *reinterpret_cast<glm::mat4*>(this) -= *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator*=(GeoMatrix4x4F other)
        {
            *reinterpret_cast<glm::mat4*>(this) *= *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator+(float other) const
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) + other);
        }

        inline GeoMatrix4x4F operator-(float other) const
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) - other);
        }

        inline GeoMatrix4x4F operator*(float other) const
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) * other);
        }

        inline GeoMatrix4x4F operator+=(float other)
        {
            *reinterpret_cast<glm::mat4*>(this) += other;
            return *this;
        }

        inline GeoMatrix4x4F operator-=(float other)
        {
            *reinterpret_cast<glm::mat4*>(this) -= other;
            return *this;
        }

        inline GeoMatrix4x4F operator*=(float other)
        {
            *reinterpret_cast<glm::mat4*>(this) *= other;
            return *this;
        }

        static GeoMatrix4x4F getDefaultIdentity()
        {
            return GeoMatrix4x4F(glm::identity<glm::mat4>());
        }
    };
} // namespace NovelRT::Maths

#endif // NOVELRT_MATHS_GEOMATRIX4_H
