// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H

namespace NovelRT {
  /**
   * Represents a 2D position, scale and rotation.
   */
  class Transform {
  protected:
    Maths::GeoVector2<float> _position;
    Maths::GeoVector2<float> _scale;
    float _rotation;
  public:
    /**
     * Creates a new Transform with the specified position, rotation and scale.
     * @param position The position which represents the position of the transform in a given space such as screen or world space.
     * @param rotation The rotation, in degrees, which represents the rotation of the transform.
     * @param scale The scale which represents the size of the transform.
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
     * Gets the bounds based on the position, scale and rotation of this transform.
     */
    inline Maths::GeoBounds getBounds() const {
      return Maths::GeoBounds(_position, _scale, _rotation);
    }

    /**
     * Gets the position of this transform. This is the read-only version.
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
     * Gets the rotation, in degrees, of this transform. This is the read-only version.
     */
    inline const float& rotation() const {
      return _rotation;
    }

    /**
     * Gets the rotation, in degrees, of this transform.
     */
    inline float& rotation() {
      return _rotation;
    }

    /**
     * Gets the scale of this transform. This is the read-only version.
     */
    inline const Maths::GeoVector2<float>& scale() const {
      return _scale;
    }

    /**
     * Gets the scale of this transform.
     */
    inline Maths::GeoVector2<float>& scale() {
      return _scale;
    }
  };
}

#endif //NOVELRT_NOVELWORLDOBJECT_H
