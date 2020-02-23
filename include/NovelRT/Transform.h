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
    int _orderInLayer;
    int _layer;
    bool _active;

  public:
    Transform(const Maths::GeoVector<float>& position, float rotation, const Maths::GeoVector<float>& scale) noexcept;
    Transform() noexcept;

    inline Maths::GeoBounds getAABB() const {
      auto scale = fmaxf(_scale.getX(), _scale.getY());
      return Maths::GeoBounds(_position, Maths::GeoVector(scale, scale), 0);
    }

    inline Maths::GeoBounds getBounds() const {
      return Maths::GeoBounds(_position, _scale, _rotation);
    }

    inline const Maths::GeoVector<float>& getPosition() const {
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

    inline const Maths::GeoVector<float>& getScale() const {
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
