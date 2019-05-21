//
// Created by matth on 30/03/2019.
//

#include "GeoBounds.h"
namespace NovelRT {
GeoBounds::GeoBounds(const NovelRT::GeoVector<float>& position, const NovelRT::GeoVector<float>& size) {
  _corners[0] = GeoVector<float>(position.getX() - (size.getX() / 2), position.getY() - (size.getY() / 2));
  _corners[1] = GeoVector<float>(position.getX() + (size.getX() / 2), position.getY() - (size.getY() / 2));
  _corners[2] = GeoVector<float>(position.getX() + (size.getX() / 2), position.getY() + (size.getY() / 2));
  _corners[3] = GeoVector<float>(position.getX() - (size.getX() / 2), position.getY() + (size.getY() / 2));
}

bool GeoBounds::pointIsWithinBounds(const GeoVector<float>& point) const {
  if (point.getX() >= _corners[0].getX() && point.getX() <= _corners[2].getX() && point.getY() <= _corners[2].getY()
      && point.getY() >= _corners[0].getY())
    return true;

  return false;
}
GeoVector<float> GeoBounds::getCornerInWorldSpace(const int index) const {
  return _corners[index];
}

GeoVector<float> GeoBounds::getCornerInOpenGLSurfaceSpace(const int index, const float scale) const {
  auto point = _corners[index];
  point.setX(point.getX() / (1920.0f * scale) - 0.5f);
  point.setY(-(point.getY() / (1080.0f * scale) - 0.5f));
  return point;
}
}