//
// Created by matth on 15/12/2018.
//
#include "NovelObject.h"

namespace NovelRT {
NovelObject::NovelObject(NovelLayeringService* layeringService, const float& screenScale,
                         const GeoVector<float>& size,
                         const NovelCommonArgs& args) :
    _screenScale(screenScale),
    _layeringService(layeringService) {
  setLayer(args.layer);
  setOrderInLayer(args.orderInLayer);
  _layeringService->updateLayerInfo(getLayer(), this, true);
  setPosition(args.startingPosition);
  setRotation(args.startingRotation);
  setWorldSpaceSize(size);
  setScale(size);
  setActive(true);
}

GeoVector<float> NovelObject::getWorldSpacePosition() const {
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

GeoVector<float> NovelObject::getWorldSpaceSize() const {
  return _size;
}

void NovelObject::setWorldSpaceSize(const GeoVector<float>& value) {
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
}
