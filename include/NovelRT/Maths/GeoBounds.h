// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class GeoBounds {
  public:
    GeoVector2F position;
    float rotation;
    GeoVector2F size;

    GeoBounds(const GeoVector2F& position, const GeoVector2F& size, float rotation) noexcept;
    bool pointIsWithinBounds(const GeoVector2F& point) const;
    bool intersectsWith(const GeoBounds& otherBounds) const;
    GeoVector2F getCornerInLocalSpace(int index) const;
    GeoVector2F getCornerInWorldSpace(int index) const;
    GeoVector2F getExtents() const;

    inline bool operator==(const GeoBounds& other) const {
      return position == other.position
          && size == other.size
          && rotation == other.rotation;
    }

    inline bool operator!=(const GeoBounds& other) const {
      return position != other.position
        || size != other.size
        || rotation != other.rotation;
    }
  };
}

#endif //!NOVELRT_MATHS_GEOBOUNDS_H
