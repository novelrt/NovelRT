// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {

  template<typename T>
  class GeoMatrix4 {
    friend class Graphics::RenderObject;
    friend class Graphics::ImageRect;
    friend class Graphics::BasicFillRect;
    friend class Graphics::TextRect;
    friend class Graphics::RenderingService;
    friend class Graphics::Camera;
  private:
    glm::mat<4, 4, T> _value;

    inline const glm::mat4& underlyingMatrix() const {
      return _value;
    }

    inline glm::mat4& underlyingMatrix() {
      return _value;
    }

    explicit GeoMatrix4(glm::mat4 matrix) {
      _value = matrix;
    }

  public:
    GeoMatrix4() {}

    GeoMatrix4(GeoVector4<T> x,
      GeoVector4<T> y,
      GeoVector4<T> z,
      GeoVector4<T> w) {
      setX(x);
      setY(y);
      setZ(z);
      setW(w);
    }

    inline GeoVector4<T> getX() const {
      return GeoVector4<T>(_value[0]);
    }

    inline void setX(const GeoVector4<T>& value) {
      _value[0] = value.vec4Value();
    }

    inline GeoVector4<T> getY() const {
      return GeoVector4<T>(_value[1]);
    }

    inline void setY(const GeoVector4<T>& value) {
      _value[1] = value.vec4Value();
    }

    inline GeoVector4<T> getZ() const {
      return GeoVector4<T>(_value[2]);
    }

    inline void setZ(const GeoVector4<T>& value) {
      _value[2] = value.vec4Value();
    }

    inline GeoVector4<T> getW() const {
      return GeoVector4<T>(_value[3]);
    }

    inline void setW(const GeoVector4<T>& value) {
      _value[3] = value.vec4Value();
    }

    inline bool operator==(const GeoMatrix4<T>& other) const {
      return underlyingMatrix() == other.underlyingMatrix();
    }

    inline bool operator!=(const GeoMatrix4<T>& other) const {
      return underlyingMatrix() != other.underlyingMatrix();
    }

    inline GeoMatrix4<T> operator+(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(underlyingMatrix() + other.underlyingMatrix());
    }

    inline GeoMatrix4<T> operator-(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(underlyingMatrix() - other.underlyingMatrix());
    }

    inline GeoMatrix4<T> operator*(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(underlyingMatrix() * other.underlyingMatrix());
    }

    inline GeoMatrix4<T> operator/(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(underlyingMatrix() / other.underlyingMatrix());
    }

    inline GeoMatrix4<T>& operator+=(const GeoMatrix4<T>& other) {
      underlyingMatrix() += other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4<T>& operator-=(const GeoMatrix4<T>& other) {
      underlyingMatrix() -= other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4<T>& operator*=(const GeoMatrix4<T>& other) {
      underlyingMatrix() *= other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4<T>& operator/=(const GeoMatrix4<T>& other) {
      underlyingMatrix() /= other.underlyingMatrix();
      return *this;
    }

    static GeoMatrix4<T> getDefaultIdentity() {
      return GeoMatrix4<T>(glm::identity<glm::mat4>());
    }
  };
}

#endif //NOVELRT_MATHS_GEOMATRIX4_H
