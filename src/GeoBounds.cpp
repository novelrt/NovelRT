//
// Created by matth on 30/03/2019.
//

#include "GeoBounds.h"
#include <math.h>

namespace NovelRT {
GeoBounds::GeoBounds(const NovelRT::GeoVector<float>& position, const NovelRT::GeoVector<float>& size, float rotation) :
    _position(position),
    _rotation(rotation),
    _size(size) {
}

bool GeoBounds::pointIsWithinBounds(const GeoVector<float>& point) const {

  return false;
}

GeoVector<float> GeoBounds::getCornerInLocalSpace(int index) const {
  GeoVector<float> returnValue;
  auto size = getSize();
  switch (index) {
  case 0:returnValue = GeoVector<float>(-(size.getX() / 2), -(size.getY() / 2));
    break;
  case 1:returnValue = GeoVector<float>(+(size.getX() / 2), -(size.getY() / 2));
    break;
  case 2:returnValue = GeoVector<float>(+(size.getX() / 2), +(size.getY() / 2));
    break;
  case 3:returnValue = GeoVector<float>(-(size.getX() / 2), +(size.getY() / 2));
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

/*GeoVector<float> GeoBounds::getCornerInOpenGLSurfaceSpace(int index, float screenScale) const {

  auto point = _corners[index];
  float pointX = ((point.getX()) / ((1920.0f * screenScale) / 2.0f)) - 1.0f;
  point.setX(pointX);
  float pointY = ( ( (point.getY()) - (1080.0f * screenScale)) / ((1080.0f * screenScale) / 2.0f)) - 1.0f;
  point.setY(pointY);
  return point;
}*/
}