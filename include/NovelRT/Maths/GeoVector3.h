// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR3_H
#define NOVELRT_MATHS_GEOVECTOR3_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template<typename T>
  class GeoVector3 {
    friend class Input::InteractionService;
    template<typename U>
    friend class GeoVector4;

  private:
    glm::vec<3, T> _value;

    GeoVector3(glm::vec<3, T> value) : _value(value) {}
    GeoVector3(glm::vec<2, T> value) : _value(glm::vec<3, T>(value, 0)) {}

    const glm::vec<3, T>& vec3Value() const {
      return _value;
    }

    glm::vec<3, T>& vec3Value() {
      return _value;
    }

  public:
    GeoVector3() {}
    GeoVector3(T x, T y, T z) : _value(glm::vec<4, T>(x, y, z, 0)) {}

    T getX() const {
      return vec3Value().x;
    }

    void setX(T value) {
      vec3Value().x = value;
    }

    T getY() const {
      return vec3Value().y;
    }

    void setY(T value) {
      vec3Value().y = value;
    }

    T getZ() const {
      return vec3Value().z;
    }

    void setZ(T value) {
      vec3Value().z = value;
    }

    inline GeoVector3<T> getNormalised() const noexcept {
      return GeoVector3<T>(glm::normalize(vec3Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(vec3Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline GeoVector4<T> asGeoVector4() const noexcept {
      return GeoVector4<T>(vec3Value(), 0);
    }

    inline bool operator==(const GeoVector3<T>& other) const {
      return vec3Value() == other.vec3Value();
    }

    inline bool operator!=(const GeoVector3<T>& other) const {
      return vec3Value() != other.vec3Value();
    }

    inline bool operator<(const GeoVector3<T>& other) const {
      return glm::any(glm::lessThan(vec3Value(), other.vec3Value()));
    }

    inline bool operator<=(const GeoVector3<T>& other) const {
      return glm::any(glm::lessThanEqual(vec3Value(), other.vec3Value()));
    }

    inline bool operator>(const GeoVector3<T>& other) const {
      return glm::any(glm::greaterThan(vec3Value(), other.vec3Value()));
    }

    inline bool operator>=(const GeoVector3<T>& other) const {
      return glm::any(glm::greaterThanEqual(vec3Value(), other.vec3Value()));
    }

    inline GeoVector3<T> operator+(const GeoVector3<T>& other) const {
      return GeoVector3<T>(vec3Value() + other.vec3Value());
    }

    inline GeoVector3<T> operator-(const GeoVector3<T>& other) const {
      return GeoVector3<T>(vec3Value() - other.vec3Value());
    }

    inline GeoVector3<T> operator*(const GeoVector3<T>& other) const {
      return GeoVector3<T>(vec3Value() * other.vec3Value());
    }

    GeoVector3<T> operator/(const GeoVector3<T>& other) const {
      return GeoVector3<T>(vec3Value() / other.vec3Value());
    }

    inline GeoVector3<T> operator+(T other) const {
      return GeoVector3<T>(vec3Value() + other);
    }

    inline GeoVector3<T> operator-(T other) const {
      return GeoVector3<T>(vec3Value() - other);
    }

    inline GeoVector3<T> operator*(T other) const {
      return GeoVector3<T>(vec3Value() * other);
    }

    GeoVector3<T> operator/(T other) const {
      return GeoVector3<T>(vec3Value() / other);
    }

    inline GeoVector3<T>& operator+=(const GeoVector3<T>& other) {
      vec3Value() = vec3Value() + other.vec3Value();
      return *this;
    }

    inline GeoVector3<T>& operator-=(const GeoVector3<T>& other) {
      vec3Value() = vec3Value() - other.vec3Value();
      return *this;
    }

    inline GeoVector3<T> operator*=(const GeoVector3<T>& other) {
      vec3Value() = vec3Value() * other.vec3Value();
      return *this;
    }

    GeoVector3<T> operator/=(const GeoVector3<T>& other) {
      vec3Value() = vec3Value() / other.vec3Value();
      return *this;
    }

    inline GeoVector3<T> operator+=(T other) {
      vec3Value() = vec3Value() + other;
      return *this;
    }

    inline GeoVector3<T> operator-=(T other) {
      vec3Value() = vec3Value() - other;
      return *this;
    }

    inline GeoVector3<T> operator*=(T other) {
      vec3Value() = vec3Value() * other;
      return *this;
    }

    GeoVector3<T> operator/=(T other) {
      vec3Value() = vec3Value() / other;
      return *this;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector3<T>& point, const GeoVector3<T>& axis = GeoVector3<T>(0, 0, 1)) noexcept {
      vec3Value() = glm::rotate((vec3Value() - point.vec3Value()), glm::radians(angleRotationValue), axis.vec3Value()) + point.vec3Value();
    }

    bool epsilonEquals(const GeoVector3<T>& other, const GeoVector3<T>& epsilonValue) const noexcept {
      return glm::all(glm::equal(vec3Value(), other.vec3Value(), epsilonValue.vec3Value()));
    }

    static const GeoVector3<T> zero() {
      return GeoVector3<T>::uniform(0);
    }

    static const GeoVector3<T> one() {
      return GeoVector3<T>::uniform(1);
    }

    static const GeoVector3<T> uniform(T value) {
      return GeoVector3<T>(value, value, value);
    }
  };

  template<typename T>
  inline GeoVector3<T> operator*(T lhs, const GeoVector3<T>& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR3_H
