// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class GeoBounds {
  private:
    GeoVector2F _position;
    float _rotation;
    GeoVector2F _size;

  public:
    GeoBounds(const GeoVector2F& position, const GeoVector2F& size, float rotation);
    bool pointIsWithinBounds(const GeoVector2F& point) const;
    bool intersectsWith(const GeoBounds& otherBounds) const;
    GeoVector2F getCornerInLocalSpace(int index) const;
    GeoVector2F getCornerInWorldSpace(int index) const;
    const GeoVector2F& position() const;
    GeoVector2F& position();
    const GeoVector2F& size() const;
    GeoVector2F& size();
    const float& rotation() const;
    float& rotation();
    GeoVector2F getExtents() const;

    inline bool operator==(const GeoBounds& other) const {
      return _position == other._position
          && _size == other._size
          && _rotation == other._rotation;
    }

    inline bool operator!=(const GeoBounds& other) const {
      return _position != other._position
        || _size != other._size
        || _rotation != other._rotation;
    }
  };
}

#endif //NOVELRT_MATHS_GEOBOUNDS_H
