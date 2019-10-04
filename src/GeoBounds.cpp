// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.
#include "GeoBounds.h"
#include <math.h>

namespace NovelRT {
GeoBounds::GeoBounds(const NovelRT::GeoVector<float>& position, const NovelRT::GeoVector<float>& size, float rotation) : _position(position) {

  _corners[0] = GeoVector<float>(position.getX() - (size.getX() / 2), position.getY() - (size.getY() / 2));
  _corners[1] = GeoVector<float>(position.getX() + (size.getX() / 2), position.getY() - (size.getY() / 2));
  _corners[2] = GeoVector<float>(position.getX() + (size.getX() / 2), position.getY() + (size.getY() / 2));
  _corners[3] = GeoVector<float>(position.getX() - (size.getX() / 2), position.getY() + (size.getY() / 2));

  rotateToAngle(rotation);
}

bool GeoBounds::pointIsWithinBounds(const GeoVector<float>& point) const {
  if (point.getX() >= _corners[0].getX() && point.getX() <= _corners[2].getX() && point.getY() <= _corners[2].getY()
      && point.getY() >= _corners[0].getY())
    return true;

  return false;
}
GeoVector<float> GeoBounds::getCornerInWorldSpace(int index) const {
  return _corners[index];
}

GeoVector<float> GeoBounds::getCornerInOpenGLSurfaceSpace(int index, float screenScale) const {
  auto point = _corners[index];
  float pointX = ((point.getX() * screenScale) / ((1920.0f * screenScale) / 2.0f)) - 1.0f;
  point.setX(pointX);
  float pointY = ((point.getY() * screenScale) / ((1080.0f * screenScale) / 2.0f)) - 1.0f;
  point.setY(pointY);
  return point;
}
void GeoBounds::rotateToAngle(float rotationAngleValue) {
  for (auto& corner : _corners) {
    corner.rotateToAngleAroundPoint(rotationAngleValue, _position);
  }
}
}