// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {
  /**
   * Represents a 2D position, scale and rotation.
   */
  class Transform {
  protected:
    Maths::GeoVector2<float> _position;
    Maths::GeoVector2<float> _scale;
    float _rotation;
    bool _active;

  public:
    /**
     * Creates a new Transform, with the specified position, rotation and scale.
     * @param position The position.
     * @param rotation The rotation.
     * @param scale The scale.
     */
    Transform(const Maths::GeoVector2<float>& position, float rotation, const Maths::GeoVector2<float>& scale) noexcept;
    /**
     * Creates a new Transform with the default values.
     */
    Transform() noexcept;

    /**
     * Gets the Axis Aligned Bounding Box based on the position and scale of this transform.
     */
    inline Maths::GeoBounds getAABB() const {
      auto scale = fmaxf(_scale.getX(), _scale.getY());
      return Maths::GeoBounds(_position, Maths::GeoVector2(scale, scale), 0);
    }

    /**
     * Gets the bounds of this transform.
     */
    inline Maths::GeoBounds getBounds() const {
      return Maths::GeoBounds(_position, _scale, _rotation);
    }

    /**
     * Gets the constant position of this transform.
     */
    inline const Maths::GeoVector2<float>& position() const {
      return _position;
    }

    /**
     * Gets the position of this transform.
     */
    inline Maths::GeoVector2<float>& position() {
      return _position;
    }

    /**
     * Gets the constant rotation of this transform.
     */
    inline const float& rotation() const {
      return _rotation;
    }

    /**
     * Gets the rotation of this transform.
     */
    inline float& rotation() {
      return _rotation;
    }

    /**
     * Gets the constant scale of this transform.
     */
    inline const Maths::GeoVector2<float>& getScale() const {
      return _scale;
    }

    /**
     * Gets the scale of this transform.
     */
    inline Maths::GeoVector2<float>& getScale() {
      return _scale;
    }

    /**
     * Sets the scale of this transform to the specified value.
     * @param value The new scale.
     */
    inline void setScale(const Maths::GeoVector2<float>& value) {
      _scale = value;
    }
  };
}

#endif //NOVELRT_NOVELWORLDOBJECT_H
