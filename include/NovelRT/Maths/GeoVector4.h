// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR4_H
#define NOVELRT_MATHS_GEOVECTOR4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template<typename T>
  class GeoVector4 {
    friend class Graphics::RenderObject;
    friend class Input::InteractionService;
    friend class GeoBounds;
    template<typename U>
    friend class GeoMatrix4x4;

  private:
    GeoVector4(glm::vec<4, T> value) : _value(value) {}

    const glm::vec<4, T>& vec4Value() const {
      return _value;
    }

    glm::vec<4, T>& vec4Value() {
      return _value;
    }

    glm::vec<4, T> _value;

  public:
    GeoVector4() {}
    GeoVector4(T x, T y, T z, T w) : _value(glm::vec<4, T>(x, y, z, w)) {}

    T getX() const {
      return _value.x;
    }

    void setX(T value) {
      _value.x = value;
    }

    T getY() const {
      return _value.y;
    }

    void setY(T value) {
      _value.y = value;
    }

    T getZ() const {
      return _value.z;
    }

    void setZ(T value) {
      _value.z = value;
    }

    T getW() const {
      return _value.w;
    }

    void setW(T value) {
      _value.w = value;
    }

    inline GeoVector4<T> getNormalised() const noexcept {
      return GeoVector4<T>(glm::normalize(vec4Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(vec4Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector4<T>& other) const {
      return vec4Value() == other.vec4Value();
    }

    inline bool operator!=(const GeoVector4<T>& other) const {
      return vec4Value() != other.vec4Value();
    }

    inline bool operator<(const GeoVector4<T>& other) const {
      return glm::any(glm::lessThan(vec4Value(), other.vec4Value()));
    }

    inline bool operator<=(const GeoVector4<T>& other) const {
      return glm::any(glm::lessThanEqual(vec4Value(), other.vec4Value()));
    }

    inline bool operator>(const GeoVector4<T>& other) const {
      return glm::any(glm::greaterThan(vec4Value(), other.vec4Value()));
    }

    inline bool operator>=(const GeoVector4<T>& other) const {
      return glm::any(glm::greaterThanEqual(vec4Value(), other.vec4Value()));
    }

    inline GeoVector4<T> operator+(const GeoVector4<T>& other) const {
      return GeoVector4<T>(vec4Value() + other.vec4Value());
    }

    inline GeoVector4<T> operator-(const GeoVector4<T>& other) const {
      return GeoVector4<T>(vec4Value() - other.vec4Value());
    }

    inline GeoVector4<T> operator*(const GeoVector4<T>& other) const {
      return GeoVector4<T>(vec4Value() * other.vec4Value());
    }

    GeoVector4<T> operator/(const GeoVector4<T>& other) const {
      return GeoVector4<T>(vec4Value() / other.vec4Value());
    }

    inline GeoVector4<T> operator+(T other) const {
      return GeoVector4<T>(vec4Value() + other);
    }

    inline GeoVector4<T> operator-(T other) const {
      return GeoVector4<T>(vec4Value() - other);
    }

    inline GeoVector4<T> operator*(T other) const {
      return GeoVector4<T>(vec4Value() * other);
    }

    GeoVector4<T> operator/(T other) const {
      return GeoVector4<T>(vec4Value() / other);
    }

    inline GeoVector4<T>& operator+=(const GeoVector4<T>& other) {
      vec4Value() += other.vec4Value();
      return *this;
    }

    inline GeoVector4<T>& operator-=(const GeoVector4<T>& other) {
      vec4Value() -= other.vec4Value();
      return *this;
    }

    inline GeoVector4<T> operator*=(const GeoVector4<T>& other) {
      vec4Value() *= other.vec4Value();
      return *this;
    }

    GeoVector4<T> operator/=(const GeoVector4<T>& other) {
      vec4Value() /= other.vec4Value();
      return *this;
    }

    inline GeoVector4<T> operator+=(T other) {
      vec4Value() += other;
      return *this;
    }

    inline GeoVector4<T> operator-=(T other) {
      vec4Value() -= other;
      return *this;
    }

    inline GeoVector4<T> operator*=(T other) {
      vec4Value() *= other;
      return *this;
    }

    GeoVector4<T> operator/=(T other) {
      vec4Value() /= other;
      return *this;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector4<T>& point, const GeoVector3<T>& axis = GeoVector3<T>(0, 0, 1)) noexcept {
      vec4Value() = glm::rotate((vec4Value() - point.vec4Value()), glm::radians(angleRotationValue), axis.getVec3Value()) + point.vec4Value();
    }

    bool epsilonEquals(const GeoVector4<T>& other, const GeoVector4<T>& epsilonValue) const noexcept {
      return glm::all(glm::equal(vec4Value(), other.vec4Value(), epsilonValue.vec4Value()));
    }

    static const GeoVector4<T> zero() {
      return GeoVector4<T>::uniform(0);
    }

    static const GeoVector4<T> one() {
      return GeoVector4<T>::uniform(1);
    }

    static const GeoVector4<T> uniform(T value) {
      return GeoVector4<T>(value, value, value, value);
    }
  };

  template<typename T>
  inline GeoVector4<T> operator*(T lhs, const GeoVector4<T>& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR4_H
