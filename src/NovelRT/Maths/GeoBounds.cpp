// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Maths {
  GeoBounds::GeoBounds(GeoVector2F position, GeoVector2F size, float rotation) noexcept :
    position(position),
    size(size),
    rotation(rotation) {}

  bool GeoBounds::pointIsWithinBounds(GeoVector2F point) const {
    auto corner0 = getCornerInWorldSpace(0);
    auto corner2 = getCornerInWorldSpace(2);

    if (point.x >= corner0.x && point.x <= corner2.x && point.y <= corner2.y
      && point.y >= corner0.y)
      return true;

    return false;
  }

  bool GeoBounds::intersectsWith(GeoBounds otherBounds) const {
    if (rotation != 0.0f) throw std::runtime_error("Box intersection does not currently support rotated bounds. AABB support only.");

    auto minA = position - getExtents();
    auto maxA = position + getExtents();
   
    auto minB = otherBounds.position - otherBounds.getExtents();
    auto maxB = otherBounds.position + otherBounds.getExtents();

    return ((minA >= maxB) || (minB >= maxA)) || ((minA <= maxB) || (minB <= maxA));
  }

  GeoVector2F GeoBounds::getCornerInLocalSpace(int index) const {
    GeoVector2F returnValue;
    auto boundsSize = size;
    switch (index) {
    case 0:
      returnValue = GeoVector2F(-(boundsSize.x / 2), -(boundsSize.y / 2));
      break;
    case 1:
      returnValue = GeoVector2F(+(boundsSize.x / 2), -(boundsSize.y / 2));
      break;
    case 2:
      returnValue = GeoVector2F(+(boundsSize.x / 2), +(boundsSize.y / 2));
      break;
    case 3:
      returnValue = GeoVector2F(-(boundsSize.x / 2), +(boundsSize.y / 2));
      break;
    }

    returnValue.rotateToAngleAroundPoint(rotation, position);
    return returnValue;
  }

  GeoVector2F GeoBounds::getCornerInWorldSpace(int index) const {
    return position + getCornerInLocalSpace(index);
  }

  GeoVector2F GeoBounds::getExtents() const {
    return size / 2.0f;
  }
}
