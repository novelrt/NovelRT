// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.
#include "NovelObject.h"
#include "GeoBounds.h"

namespace NovelRT {
NovelObject::NovelObject(NovelLayeringService* layeringService,
                         const GeoVector<float>& size,
                         const NovelCommonArgs& args) :
    _layeringService(layeringService) {
  setLayer(args.layer);
  setOrderInLayer(args.orderInLayer);
  _layeringService->updateLayerInfo(getLayer(), this, true);
  setPosition(args.startingPosition);
  setRotation(args.startingRotation);
  setSize(size);
  setScale(args.startingScale);
  setActive(true);
}

NovelObject::~NovelObject() = default;

GeoVector<float> NovelObject::getPosition() const {
  return _position;
}

void NovelObject::setPosition(const GeoVector<float>& value) {
  _position = value;
}

float NovelObject::getRotation() const {
  return _rotation;
}

void NovelObject::setRotation(const float value) {
  _rotation = value;
}

GeoVector<float> NovelObject::getScale() const {
  return _scale;
}

void NovelObject::setScale(const GeoVector<float>& value) {
  _scale = value;
}

GeoVector<float> NovelObject::getSize() const {
  return _size;
}

void NovelObject::setSize(const GeoVector<float>& value) {
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

/*GeoBounds NovelObject::getScreenSpaceObjectBounds() {
  if(_isDirty) {
  _isDirty = false;
  GeoVector<float> position = getScreenSpacePosition();
  GeoVector<float> size = getScreenSpaceSize();
  _objectBounds = GeoBounds(position, size, getRotation());
  }
  return _objectBounds;
}*/

}
