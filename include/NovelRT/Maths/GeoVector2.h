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
    friend class GeoBounds;
    template<typename U>
    friend class GeoMatrix4;

  private:
    GeoVector2(glm::vec<2, T> value) : _value(glm::vec<4, T>(value, 0, 0)) {}
    GeoVector2(glm::vec<4, T> value) : _value(value) {}

    inline glm::vec<2, T> getVec2Value() const {
      return glm::vec<2, T>(_value.x, _value.y);
    }

    inline void setVec2Value(glm::vec<2, T> value) {
      _value.x = value.x;
      _value.y = value.y;
    }

    const glm::vec<4, T>& vec4Value() const {
      return _value;
    }

    glm::vec<4, T>& vec4Value() {
      return _value;
    }

    glm::vec<4, T> _value;

  public:
    GeoVector2() {}
    GeoVector2(T x, T y) : _value(glm::vec<4, T>(x, y, 0, 0)) {}

    T getX() const {
      return getVec2Value().x;
    }

    void setX(T value) {
      _value.x = value;
    }

    T getY() const {
      return getVec2Value().y;
    }

    void setY(T value) {
      _value.y = value;
    }

    inline GeoVector2<T> getNormalised() const noexcept {
      return GeoVector2<T>(glm::normalize(getVec2Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(getVec2Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector2<T>& other) const {
      return getVec2Value() == other.getVec2Value();
    }

    inline bool operator!=(const GeoVector2<T>& other) const {
      return getVec2Value() != other.getVec2Value();
    }

    inline bool operator<(const GeoVector2<T>& other) const {
      return glm::any(glm::lessThan(getVec2Value(), other.getVec2Value()));
    }

    inline bool operator<=(const GeoVector2<T>& other) const {
      return glm::any(glm::lessThanEqual(getVec2Value(), other.getVec2Value()));
    }

    inline bool operator>(const GeoVector2<T>& other) const {
      return glm::any(glm::greaterThan(getVec2Value(), other.getVec2Value()));
    }

    inline bool operator>=(const GeoVector2<T>& other) const {
      return glm::any(glm::greaterThanEqual(getVec2Value(), other.getVec2Value()));
    }

    inline GeoVector2<T> operator+(const GeoVector2<T>& other) const {
      return GeoVector2<T>(getVec2Value() + other.getVec2Value());
    }

    inline GeoVector2<T> operator-(const GeoVector2<T>& other) const {
      return GeoVector2<T>(getVec2Value() - other.getVec2Value());
    }

    inline GeoVector2<T> operator*(const GeoVector2<T>& other) const {
      return GeoVector2<T>(getVec2Value() * other.getVec2Value());
    }

    GeoVector2<T> operator/(const GeoVector2<T>& other) const {
      return GeoVector2<T>(getVec2Value() / other.getVec2Value());
    }

    inline GeoVector2<T> operator+(T other) const {
      return GeoVector2<T>(getVec2Value() + other);
    }

    inline GeoVector2<T> operator-(T other) const {
      return GeoVector2<T>(getVec2Value() - other);
    }

    inline GeoVector2<T> operator*(T other) const {
      return GeoVector2<T>(getVec2Value() * other);
    }

    GeoVector2<T> operator/(T other) const {
      return GeoVector2<T>(getVec2Value() / other);
    }

    inline GeoVector2<T>& operator+=(const GeoVector2<T>& other) {
      setVec2Value(getVec2Value() + other.getVec2Value());
      return *this;
    }

    inline GeoVector2<T>& operator-=(const GeoVector2<T>& other) {
      setVec2Value(getVec2Value() - other.getVec2Value());
      return *this;
    }

    inline GeoVector2<T> operator*=(const GeoVector2<T>& other) {
      setVec2Value(getVec2Value() * other.getVec2Value());
      return *this;
    }

    GeoVector2<T> operator/=(const GeoVector2<T>& other) {
      setVec2Value(getVec2Value() / other.getVec2Value());
      return *this;
    }

    inline GeoVector2<T> operator+=(T other) {
      setVec2Value(getVec2Value() + other);
      return *this;
    }

    inline GeoVector2<T> operator-=(T other) {
      setVec2Value(getVec2Value() - other);
      return *this;
    }

    inline GeoVector2<T> operator*=(T other) {
      setVec2Value(getVec2Value() * other);
      return *this;
    }

    GeoVector2<T> operator/=(T other) {
      setVec2Value(getVec2Value() / other);
      return *this;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector2<T>& point) noexcept {
      setVec2Value(glm::rotate((getVec2Value() - point.getVec2Value()), glm::radians(angleRotationValue)) + point.getVec2Value());
    }

    bool epsilonEquals(const GeoVector2<T>& other, const GeoVector2<T>& epsilonValue) const noexcept {
      return glm::all(glm::equal(getVec2Value(), other.getVec2Value(), epsilonValue.getVec2Value()));
    }

    static const GeoVector2<T> zero() {
      return GeoVector2<T>(0, 0);
    }

    static const GeoVector2<T> one() {
      return GeoVector2<T>(1, 1);
    }
  };
}

#endif //!NOVELRT_MATHS_GEOVECTOR2_H
