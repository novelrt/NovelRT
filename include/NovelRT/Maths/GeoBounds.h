// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
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
        [[nodiscard]] bool pointIsWithinBounds(GeoVector2F point) const noexcept;
        [[nodiscard]] bool intersectsWith(GeoBounds otherBounds) const;
        [[nodiscard]] GeoVector2F getCornerInLocalSpace(int32_t index) const noexcept;
        [[nodiscard]] GeoVector2F getCornerInWorldSpace(int32_t index) const noexcept;
        [[nodiscard]] GeoVector2F getExtents() const noexcept;

        inline bool operator==(GeoBounds other) const noexcept
        {
            return position == other.position && size == other.size && rotation == other.rotation;
        }

        inline bool operator!=(GeoBounds other) const noexcept
        {
            return position != other.position || size != other.size || rotation != other.rotation;
        }
    };
}

#endif //! NOVELRT_MATHS_GEOBOUNDS_H
