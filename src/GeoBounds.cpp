// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "GeoBounds.h"
#include <math.h>

namespace NovelRT {
  GeoBounds::GeoBounds(const NovelRT::GeoVector<float>& position, const NovelRT::GeoVector<float>& size, float rotation) :
    _position(position),
    _rotation(rotation),
    _size(size) {
  }

  bool GeoBounds::pointIsWithinBounds(const GeoVector<float>& point) const {
    if (point.getX() >= getCornerInWorldSpace(0).getX() && point.getX() <= getCornerInWorldSpace(2).getX() && point.getY() <= getCornerInWorldSpace(2).getY()
      && point.getY() >= getCornerInWorldSpace(0).getY())
      return true;

    return false;
  }

  GeoVector<float> GeoBounds::getCornerInLocalSpace(int index) const {
    GeoVector<float> returnValue;
    auto size = getSize();
    switch (index) {
    case 0:
      returnValue = GeoVector<float>(-(size.getX() / 2), -(size.getY() / 2));
      break;
    case 1:
      returnValue = GeoVector<float>(+(size.getX() / 2), -(size.getY() / 2));
      break;
    case 2:
      returnValue = GeoVector<float>(+(size.getX() / 2), +(size.getY() / 2));
      break;
    case 3:
      returnValue = GeoVector<float>(-(size.getX() / 2), +(size.getY() / 2));
      break;
    }

    returnValue.rotateToAngleAroundPoint(getRotation(), getPosition());
    return returnValue;
  }

  GeoVector<float> GeoBounds::getCornerInWorldSpace(int index) const {
    return _position + getCornerInLocalSpace(index);
  }

  GeoVector<float> GeoBounds::getPosition() const {
    return _position;
  }

  void GeoBounds::setPosition(const GeoVector<float>& value) {
    _position = value;
  }

  GeoVector<float> GeoBounds::getSize() const {
    return _size;
  }
  void GeoBounds::setSize(const GeoVector<float>& value) {
    _size = value;
  }
  float GeoBounds::getRotation() const {
    return _rotation;
  }
  void GeoBounds::setRotation(float value) {
    _rotation = value;
  }
}
