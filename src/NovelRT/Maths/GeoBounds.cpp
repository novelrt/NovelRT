// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Maths {
  GeoBounds::GeoBounds(const GeoVector<float>& position, const GeoVector<float>& size, float rotation) :
    _position(position),
    _rotation(rotation),
    _size(size) { }

  bool GeoBounds::pointIsWithinBounds(const GeoVector<float>& point) const {
    auto corner0 = getCornerInWorldSpace(0);
    auto corner2 = getCornerInWorldSpace(2);

    if (point.getX() >= corner0.getX() && point.getX() <= corner2.getX() && point.getY() <= corner2.getY()
      && point.getY() >= corner0.getY())
      return true;

    return false;
  }

  bool GeoBounds::intersectsWith(const GeoBounds& otherBounds) const {
    if (rotation() != 0.0f) throw std::runtime_error("Box intersection does not currently support rotated bounds. AABB support only.");

    auto minA = position() - getExtents();
    auto maxA = position() + getExtents();

    auto minB = otherBounds.position() - otherBounds.getExtents();
    auto maxB = otherBounds.position() + otherBounds.getExtents();

    auto result = glm::greaterThan(minA.getVec2Value(), maxB.getVec2Value()) | glm::greaterThan(minB.getVec2Value(), maxA.getVec2Value());
    return glm::any(result);
  }

  GeoVector<float> GeoBounds::getCornerInLocalSpace(int index) const {
    GeoVector<float> returnValue;
    auto boundsSize = size();
    switch (index) {
    case 0:
      returnValue = GeoVector<float>(-(boundsSize.getX() / 2), -(boundsSize.getY() / 2));
      break;
    case 1:
      returnValue = GeoVector<float>(+(boundsSize.getX() / 2), -(boundsSize.getY() / 2));
      break;
    case 2:
      returnValue = GeoVector<float>(+(boundsSize.getX() / 2), +(boundsSize.getY() / 2));
      break;
    case 3:
      returnValue = GeoVector<float>(-(boundsSize.getX() / 2), +(boundsSize.getY() / 2));
      break;
    }

    returnValue.rotateToAngleAroundPoint(rotation(), position());
    return returnValue;
  }

  GeoVector<float> GeoBounds::getCornerInWorldSpace(int index) const {
    return _position + getCornerInLocalSpace(index);
  }

  const GeoVector<float>& GeoBounds::position() const {
    return _position;
  }

  GeoVector<float>& GeoBounds::position() {
    return _position;
  }

  const GeoVector<float>& GeoBounds::size() const {
    return _size;
  }

  GeoVector<float>& GeoBounds::size() {
    return _size;
  }

  const float& GeoBounds::rotation() const {
    return _rotation;
  }

  float& GeoBounds::rotation() {
    return _rotation;
  }

  GeoVector<float> GeoBounds::getExtents() const {
    return _size / 2.0f;
  }
}
