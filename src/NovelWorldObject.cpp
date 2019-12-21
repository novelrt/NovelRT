// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "../include/NovelWorldObject.h"
#include "../include/GeoBounds.h"

namespace NovelRT {
  NovelWorldObject::NovelWorldObject(NovelLayeringService* layeringService,
    const NovelCommonArgs& args) :
    _layeringService(layeringService) {
    setLayer(args.layer);
    setOrderInLayer(args.orderInLayer);
    _layeringService->updateLayerInfo(getLayer(), this, true);
    setPosition(args.startingPosition);
    setRotation(args.startingRotation);
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

  bool NovelWorldObject::getActive() const {
    return _active;
  }

  void NovelWorldObject::setActive(const bool value) {
    _active = value;
  }

  int NovelWorldObject::getLayer() const {
    return _layer;
  }

  void NovelWorldObject::setLayer(int value) {
    _layer = value;
    _layeringService->updateLayerInfo(value, this);
  }

  int NovelWorldObject::getOrderInLayer() const {
    return _orderInLayer;
  }

  void NovelWorldObject::setOrderInLayer(int value) {
    _orderInLayer = value;
    _layeringService->sortLayerOrder(getLayer());
  }
}
