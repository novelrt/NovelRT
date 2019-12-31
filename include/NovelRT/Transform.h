// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H
#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {
  class Transform {
  protected:
    Maths::GeoVector<float> _position;
    Maths::GeoVector<float> _scale;
    float _rotation;
    bool _active = true;
    int _orderInLayer;
    int _layer;

  public:
    Transform(const Maths::GeoVector<float>& position, float rotation, const Maths::GeoVector<float>& scale);

  inline const Maths::GeoVector<float>& getPositionReadonly() const {
    return _position;
  }

  inline Maths::GeoVector<float>& getPosition() {
    return _position;
  }

  inline void setPosition(const Maths::GeoVector<float>& value) {
    _position = value;
  }

  inline float getRotation() const {
    return _rotation;
  }

  inline void setRotation(const float value) {
    _rotation = value;
  }

  inline const Maths::GeoVector<float>& getScaleReadonly() const {
    return _scale;
  }

  inline Maths::GeoVector<float>& getScale() {
    return _scale;
  }

  inline void setScale(const Maths::GeoVector<float>& value) {
    _scale = value;
  }
  };
}
#endif //NOVELRT_NOVELWORLDOBJECT_H
