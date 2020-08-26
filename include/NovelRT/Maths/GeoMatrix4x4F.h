// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {

  class GeoMatrix4x4F {
    friend class Graphics::RenderObject;
    friend class Graphics::ImageRect;
    friend class Graphics::BasicFillRect;
    friend class Graphics::TextRect;
    friend class Graphics::RenderingService;
    friend class Graphics::Camera;
  private:
    glm::mat4 _value;

    inline const glm::mat4& underlyingMatrix() const {
      return _value;
    }

    inline glm::mat4& underlyingMatrix() {
      return _value;
    }

    explicit GeoMatrix4x4F(glm::mat4 matrix) {
      _value = matrix;
    }

  public:
    GeoMatrix4x4F() {}

    GeoMatrix4x4F(GeoVector4F x,
      GeoVector4F y,
      GeoVector4F z,
      GeoVector4F w) {
      setX(x);
      setY(y);
      setZ(z);
      setW(w);
    }

    inline GeoVector4F getX() const {
      return GeoVector4F(_value[0]);
    }

    inline void setX(const GeoVector4F& value) {
      _value[0] = value.vec4Value();
    }

    inline GeoVector4F getY() const {
      return GeoVector4F(_value[1]);
    }

    inline void setY(const GeoVector4F& value) {
      _value[1] = value.vec4Value();
    }

    inline GeoVector4F getZ() const {
      return GeoVector4F(_value[2]);
    }

    inline void setZ(const GeoVector4F& value) {
      _value[2] = value.vec4Value();
    }

    inline GeoVector4F getW() const {
      return GeoVector4F(_value[3]);
    }

    inline void setW(const GeoVector4F& value) {
      _value[3] = value.vec4Value();
    }

    inline bool operator==(const GeoMatrix4x4F& other) const {
      return underlyingMatrix() == other.underlyingMatrix();
    }

    inline bool operator!=(const GeoMatrix4x4F& other) const {
      return underlyingMatrix() != other.underlyingMatrix();
    }

    inline GeoMatrix4x4F operator+(const GeoMatrix4x4F& other) const {
      return GeoMatrix4x4F(underlyingMatrix() + other.underlyingMatrix());
    }

    inline GeoMatrix4x4F operator-(const GeoMatrix4x4F& other) const {
      return GeoMatrix4x4F(underlyingMatrix() - other.underlyingMatrix());
    }

    inline GeoMatrix4x4F operator*(const GeoMatrix4x4F& other) const {
      return GeoMatrix4x4F(underlyingMatrix() * other.underlyingMatrix());
    }

    inline GeoMatrix4x4F& operator+=(const GeoMatrix4x4F& other) {
      underlyingMatrix() += other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4x4F& operator-=(const GeoMatrix4x4F& other) {
      underlyingMatrix() -= other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4x4F& operator*=(const GeoMatrix4x4F& other) {
      underlyingMatrix() *= other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4x4F operator+(float other) const {
      return GeoMatrix4x4F(underlyingMatrix() + other);
    }

    inline GeoMatrix4x4F operator-(float other) const {
      return GeoMatrix4x4F(underlyingMatrix() - other);
    }

    inline GeoMatrix4x4F operator*(float other) const {
      return GeoMatrix4x4F(underlyingMatrix() * other);
    }

    inline GeoMatrix4x4F& operator+=(float other) {
      underlyingMatrix() += other;
      return *this;
    }

    inline GeoMatrix4x4F& operator-=(float other) {
      underlyingMatrix() -= other;
      return *this;
    }

    inline GeoMatrix4x4F& operator*=(float other) {
      underlyingMatrix() *= other;
      return *this;
    }

    static GeoMatrix4x4F getDefaultIdentity() {
      return GeoMatrix4x4F(glm::identity<glm::mat4>());
    }
  };
}

#endif //NOVELRT_MATHS_GEOMATRIX4_H
