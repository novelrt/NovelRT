//
// Created by matth on 15/12/2018.
//
#include "NovelObject.h"
#include "GeoBounds.h"

namespace NovelRT {
NovelObject::NovelObject(NovelLayeringService* layeringService, const float& screenScale,
                         const GeoVector<float>& size,
                         const NovelCommonArgs& args) :
    _screenScale(screenScale),
    _layeringService(layeringService) {
  setLayer(args.layer);
  setOrderInLayer(args.orderInLayer);
  _layeringService->updateLayerInfo(getLayer(), this, true);
  setWorldSpacePosition(args.startingPosition);
  setRotation(args.startingRotation);
  setWorldSpaceSize(size);
  setScale(args.startingScale);
  setActive(true);
}

GeoVector<float> NovelObject::getWorldSpacePosition() const {
  return _position;
}

void NovelObject::setWorldSpacePosition(const GeoVector<float>& value) {
  _isDirty = true;
  _position = value;
}

float NovelObject::getRotation() const {
  return _rotation;
}

void NovelObject::setRotation(const float value) {
  _isDirty = true;
  _rotation = value;
}

GeoVector<float> NovelObject::getScale() const {
  return _scale;
}

void NovelObject::setScale(const GeoVector<float>& value) {
  _isDirty = true;
  _scale = value;
}

GeoVector<float> NovelObject::getWorldSpaceSize() const {
  return _size;
}

void NovelObject::setWorldSpaceSize(const GeoVector<float>& value) {
  _isDirty = true;
  _size = value;
}

bool NovelObject::getActive() const {
  return _active;
}

void NovelObject::setActive(const bool value) {
  _active = value;
}

int NovelObject::getLayer() const {
  return _layer;
}

void NovelObject::setLayer(const int value) {
  _layer = value;
  _layeringService->updateLayerInfo(value, this);

}

int NovelObject::getOrderInLayer() const {
  return _orderInLayer;
}

void NovelObject::setOrderInLayer(const int value) {
  _orderInLayer = value;
  _layeringService->sortLayerOrder(getLayer());
}

GeoBounds NovelObject::getScreenSpaceObjectBounds() {
  if(_isDirty) {
  _isDirty = false;
  GeoVector<float> position = getWorldSpacePosition();
  GeoVector<float> size = (getWorldSpaceSize() * getScale());
  _objectBounds = GeoBounds(position, size, getRotation());
  }
  return _objectBounds;
}
float NovelObject::getScaleHypotenuseScalar() const {
  auto scale = getScale();
  return scale.getX() * scale.getY();
}
GeoVector<float> NovelObject::getScreenSpaceSize() const {
  return getWorldSpaceSize() * _screenScale;
}
GeoVector<float> NovelObject::getScreenSpacePosition() const {
  return getWorldSpacePosition() * _screenScale;
}
void NovelObject::destroy() {
  _layeringService->deleteFromMatrix(this, true);
}
}
