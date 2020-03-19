// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR2_H
#define NOVELRT_MATHS_GEOVECTOR2_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template<typename T>
  class GeoVector2 {
    friend class Graphics::RenderObject;
    friend class Input::InteractionService;

  private:
    glm::vec<2, T> _value;

    GeoVector2(glm::vec<2, T> value) : _value(glm::vec<2, T>(value)) {}

    const glm::vec<2, T>& vec2Value() const {
      return _value;
    }

    glm::vec<2, T>& vec2Value() {
      return _value;
    }

  public:
    GeoVector2() {}
    GeoVector2(T x, T y) : _value(glm::vec<4, T>(x, y, 0, 0)) {}

    T getX() const {
      return vec2Value().x;
    }

    void setX(T value) {
      vec2Value().x = value;
    }

    T getY() const {
      return vec2Value().y;
    }

    void setY(T value) {
      vec2Value().y = value;
    }

    inline GeoVector2<T> getNormalised() const noexcept {
      return GeoVector2<T>(glm::normalize(vec2Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(vec2Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline GeoVector3<T> asGeoVector3() const noexcept {
      return GeoVector3<T>(vec2Value());
    }

    inline GeoVector4<T> asGeoVector4() const noexcept {
      return GeoVector4<T>(vec2Value());
    }

    inline bool operator==(const GeoVector2<T>& other) const {
      return vec2Value() == other.vec2Value();
    }

    inline bool operator!=(const GeoVector2<T>& other) const {
      return vec2Value() != other.vec2Value();
    }

    inline bool operator<(const GeoVector2<T>& other) const {
      return glm::any(glm::lessThan(vec2Value(), other.vec2Value()));
    }

    inline bool operator<=(const GeoVector2<T>& other) const {
      return glm::any(glm::lessThanEqual(vec2Value(), other.vec2Value()));
    }

    inline bool operator>(const GeoVector2<T>& other) const {
      return glm::any(glm::greaterThan(vec2Value(), other.vec2Value()));
    }

    inline bool operator>=(const GeoVector2<T>& other) const {
      return glm::any(glm::greaterThanEqual(vec2Value(), other.vec2Value()));
    }

    inline GeoVector2<T> operator+(const GeoVector2<T>& other) const {
      return GeoVector2<T>(vec2Value() + other.vec2Value());
    }

    inline GeoVector2<T> operator-(const GeoVector2<T>& other) const {
      return GeoVector2<T>(vec2Value() - other.vec2Value());
    }

    inline GeoVector2<T> operator*(const GeoVector2<T>& other) const {
      return GeoVector2<T>(vec2Value() * other.vec2Value());
    }

    GeoVector2<T> operator/(const GeoVector2<T>& other) const {
      return GeoVector2<T>(vec2Value() / other.vec2Value());
    }

    inline GeoVector2<T> operator+(T other) const {
      return GeoVector2<T>(vec2Value() + other);
    }

    inline GeoVector2<T> operator-(T other) const {
      return GeoVector2<T>(vec2Value() - other);
    }

    inline GeoVector2<T> operator*(T other) const {
      return GeoVector2<T>(vec2Value() * other);
    }

    GeoVector2<T> operator/(T other) const {
      return GeoVector2<T>(vec2Value() / other);
    }

    inline GeoVector2<T>& operator+=(const GeoVector2<T>& other) {
      vec2Value() = vec2Value() + other.vec2Value();
      return *this;
    }

    inline GeoVector2<T>& operator-=(const GeoVector2<T>& other) {
      vec2Value() = vec2Value() - other.vec2Value();
      return *this;
    }

    inline GeoVector2<T> operator*=(const GeoVector2<T>& other) {
      vec2Value() = vec2Value() * other.vec2Value();
      return *this;
    }

    GeoVector2<T> operator/=(const GeoVector2<T>& other) {
      vec2Value() = vec2Value() / other.vec2Value();
      return *this;
    }

    inline GeoVector2<T> operator+=(T other) {
      vec2Value() = vec2Value() + other;
      return *this;
    }

    inline GeoVector2<T> operator-=(T other) {
      vec2Value() = vec2Value() - other;
      return *this;
    }

    inline GeoVector2<T> operator*=(T other) {
      vec2Value() = vec2Value() * other;
      return *this;
    }

    GeoVector2<T> operator/=(T other) {
      vec2Value() = vec2Value() / other;
      return *this;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector2<T>& point) noexcept {
      vec2Value() = glm::rotate((vec2Value() - point.vec2Value()), glm::radians(angleRotationValue)) + point.vec2Value();
    }

    bool epsilonEquals(const GeoVector2<T>& other, const GeoVector2<T>& epsilonValue) const noexcept {
      return glm::all(glm::equal(vec2Value(), other.vec2Value(), epsilonValue.vec2Value()));
    }

    static const GeoVector2<T> zero() {
      return GeoVector2<T>::uniform(0);
    }

    static const GeoVector2<T> one() {
      return GeoVector2<T>::uniform(1);
    }

    static const GeoVector2<T> uniform(T value) {
      return GeoVector2<T>(value, value);
    }
  };

  template<typename T>
  inline GeoVector2<T> operator*(T lhs, const GeoVector2<T>& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR2_H
