// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths
{
    class GeoBounds
    {
    public:
        GeoVector2F position;
        GeoVector2F size;
        float rotation;

        GeoBounds(GeoVector2F position, GeoVector2F size, float rotation) noexcept;
        bool pointIsWithinBounds(GeoVector2F point) const;
        bool intersectsWith(GeoBounds otherBounds) const;
        GeoVector2F getCornerInLocalSpace(int32_t index) const;
        GeoVector2F getCornerInWorldSpace(int32_t index) const;
        GeoVector2F getExtents() const;

        inline bool operator==(GeoBounds other) const
        {
            return position == other.position && size == other.size && rotation == other.rotation;
        }

        inline bool operator!=(GeoBounds other) const
        {
            return position != other.position || size != other.size || rotation != other.rotation;
        }

        /**
         * @brief Gets the Axis Aligned Bounding Box based on the position and scale of the specified transform.
         */
        static inline Maths::GeoBounds GetAABBFromTransform(Transform transform)
        {
            auto maxFscale = fmaxf(transform.scale.x, transform.scale.y);
            return GeoBounds(transform.position, Maths::GeoVector2F(maxFscale, maxFscale), 0);
        }

        /**
         * @brief Gets the bounds based on the position, scale and rotation of the specified transform.
         */
        static inline Maths::GeoBounds FromTransform(Transform transform)
        {
            return GeoBounds(transform.position, transform.scale, transform.rotation);
        }
    };
} // namespace NovelRT::Maths

#endif //! NOVELRT_MATHS_GEOBOUNDS_H
