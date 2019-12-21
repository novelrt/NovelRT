// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>

namespace NovelRT {
  Transform::Transform(LayeringService* layeringService,
    const Utilities::CommonArgs& args) :
    _layeringService(layeringService) {
    setLayer(args.layer);
    setOrderInLayer(args.orderInLayer);
    _layeringService->updateLayerInfo(getLayer(), this, true);
    setPosition(args.startingPosition);
    setRotation(args.startingRotation);
    setScale(args.startingScale);
    setActive(true);
  }

  Transform::~Transform() = default;

  GeoVector<float> Transform::getPosition() const {
    return _position;
  }

  void Transform::setPosition(const GeoVector<float>& value) {
    _position = value;
  }

  float Transform::getRotation() const {
    return _rotation;
  }

  void Transform::setRotation(const float value) {
    _rotation = value;
  }

  GeoVector<float> Transform::getScale() const {
    return _scale;
  }

  void Transform::setScale(const GeoVector<float>& value) {
    _scale = value;
  }

  bool Transform::getActive() const {
    return _active;
  }

  void Transform::setActive(const bool value) {
    _active = value;
  }

  int Transform::getLayer() const {
    return _layer;
  }

  void Transform::setLayer(int value) {
    _layer = value;
    _layeringService->updateLayerInfo(value, this);
  }

  int Transform::getOrderInLayer() const {
    return _orderInLayer;
  }

  void Transform::setOrderInLayer(int value) {
    _orderInLayer = value;
    _layeringService->sortLayerOrder(getLayer());
  }
}
