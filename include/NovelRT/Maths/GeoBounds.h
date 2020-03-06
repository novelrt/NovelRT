// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

namespace NovelRT::Maths {
  class GeoBounds {
  private:
    GeoVector2<float> _position;
    float _rotation;
    GeoVector2<float> _size;

  public:
    GeoBounds(const GeoVector2<float>& position, const GeoVector2<float>& size, float rotation);
    bool pointIsWithinBounds(const GeoVector2<float>& point) const;
    bool intersectsWith(const GeoBounds& otherBounds) const;
    GeoVector2<float> getCornerInLocalSpace(int index) const;
    GeoVector2<float> getCornerInWorldSpace(int index) const;
    const GeoVector2<float>& position() const;
    GeoVector2<float>& position();
    const GeoVector2<float>& size() const;
    GeoVector2<float>& size();
    const float& rotation() const;
    float& rotation();
    GeoVector2<float> getExtents() const;

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
