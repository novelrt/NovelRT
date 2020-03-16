// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {
  class Transform {
  protected:
    Maths::GeoVector2<float> _position;
    Maths::GeoVector2<float> _scale;
    float _rotation;
    bool _active;

  public:
    Transform(const Maths::GeoVector2<float>& position, float rotation, const Maths::GeoVector2<float>& scale) noexcept;
    Transform() noexcept;

    inline Maths::GeoBounds getAABB() const {
      auto scale = fmaxf(_scale.getX(), _scale.getY());
      return Maths::GeoBounds(_position, Maths::GeoVector2(scale, scale), 0);
    }

    inline Maths::GeoBounds getBounds() const {
      return Maths::GeoBounds(_position, _scale, _rotation);
    }

    inline const Maths::GeoVector2<float>& position() const {
      return _position;
    }

    inline Maths::GeoVector2<float>& position() {
      return _position;
    }

    inline float getRotation() const {
      return _rotation;
    }

    inline void setRotation(const float value) {
      _rotation = value;
    }

    inline const Maths::GeoVector2<float>& getScale() const {
      return _scale;
    }

    inline Maths::GeoVector2<float>& getScale() {
      return _scale;
    }

    inline void setScale(const Maths::GeoVector2<float>& value) {
      _scale = value;
    }
  };
}

#endif //NOVELRT_NOVELWORLDOBJECT_H
