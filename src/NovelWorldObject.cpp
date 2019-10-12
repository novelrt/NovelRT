// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.
#include "NovelWorldObject.h"
#include "GeoBounds.h"

namespace NovelRT {
NovelWorldObject::NovelWorldObject(NovelLayeringService* layeringService,
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

NovelWorldObject::~NovelWorldObject() = default;

GeoVector<float> NovelWorldObject::getPosition() const {
  return _position;
}

void NovelWorldObject::setPosition(const GeoVector<float>& value) {
  _position = value;
}

float NovelWorldObject::getRotation() const {
  return _rotation;
}

void NovelWorldObject::setRotation(const float value) {
  _rotation = value;
}

GeoVector<float> NovelWorldObject::getScale() const {
  return _scale;
}

void NovelWorldObject::setScale(const GeoVector<float>& value) {
  _scale = value;
}

GeoVector<float> NovelWorldObject::getSize() const {
  return _size;
}

void NovelWorldObject::setSize(const GeoVector<float>& value) {
  _size = value;
}

bool NovelWorldObject::getActive() const {
  return _active;
}

void NovelWorldObject::setActive(const bool value) {
  _active = value;
}

int NovelWorldObject::getLayer() const {
  return _layer;
}

void NovelWorldObject::setLayer(const int value) {
  _layer = value;
  _layeringService->updateLayerInfo(value, this);

}

int NovelWorldObject::getOrderInLayer() const {
  return _orderInLayer;
}

void NovelWorldObject::setOrderInLayer(const int value) {
  _orderInLayer = value;
  _layeringService->sortLayerOrder(getLayer());
}

/*GeoBounds NovelWorldObject::getScreenSpaceObjectBounds() {
  if(_isDirty) {
  _isDirty = false;
  GeoVector<float> position = getScreenSpacePosition();
  GeoVector<float> size = getScreenSpaceSize();
  _objectBounds = GeoBounds(position, size, getRotation());
  }
  return _objectBounds;
}*/

}
