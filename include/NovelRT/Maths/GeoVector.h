// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR_H
#define NOVELRT_MATHS_GEOVECTOR_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template<typename T>
  class GeoVector {
    friend class Graphics::RenderObject;
    friend class Input::InteractionService;
    friend class GeoBounds;
    template<typename U>
    friend class GeoMatrix4;

  private:
    GeoVector(glm::vec<2, T> value) : _value(glm::vec<4, T>(value, 0, 0)) {}
    GeoVector(glm::vec<4, T> value) : _value(value) {}

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
    GeoVector() {}
    GeoVector(T x, T y) : _value(glm::vec<4, T>(x, y, 0, 0)) {}

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

    inline GeoVector<T> getNormalised() const noexcept {
      return GeoVector<T>(glm::normalize(getVec2Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(getVec2Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector<T>& other) const {
      return getVec2Value() == other.getVec2Value();
    }

    inline bool operator!=(const GeoVector<T>& other) const {
      return getVec2Value() != other.getVec2Value();
    }

    inline GeoVector<T> operator+(const GeoVector<T>& other) const {
      return GeoVector<T>(getVec2Value() + other.getVec2Value());
    }

    inline GeoVector<T> operator-(const GeoVector<T>& other) const {
      return GeoVector<T>(getVec2Value() - other.getVec2Value());
    }

    inline GeoVector<T> operator*(const GeoVector<T>& other) const {
      return GeoVector<T>(getVec2Value() * other.getVec2Value());
    }

    GeoVector<T> operator/(const GeoVector<T>& other) const {
      return GeoVector<T>(getVec2Value() / other.getVec2Value());
    }

    inline GeoVector<T> operator+(T other) const {
      return GeoVector<T>(getVec2Value() + other);
    }

    inline GeoVector<T> operator-(T other) const {
      return GeoVector<T>(getVec2Value() - other);
    }

    inline GeoVector<T> operator*(T other) const {
      return GeoVector<T>(getVec2Value() * other);
    }

    GeoVector<T> operator/(T other) const {
      return GeoVector<T>(getVec2Value() / other);
    }

    inline GeoVector<T>& operator+=(const GeoVector<T>& other) {
      vec4Value() += other.vec4Value();
      return *this;
    }

    inline GeoVector<T>& operator-=(const GeoVector<T>& other) {
      vec4Value() -= other.vec4Value();
      return *this;
    }

    inline GeoVector<T> operator*=(const GeoVector<T>& other) {
      vec4Value() *= other.vec4Value();
      return *this;
    }

    GeoVector<T> operator/=(const GeoVector<T>& other) {
      vec4Value() /= other.vec4Value();
      return *this;
    }

    inline GeoVector<T> operator+=(T other) {
      vec4Value() += other;
      return *this;
    }

    inline GeoVector<T> operator-=(T other) {
      vec4Value() -= other;
      return *this;
    }

    inline GeoVector<T> operator*=(T other) {
      vec4Value() *= other;
      return *this;
    }

    GeoVector<T> operator/=(T other) {
      vec4Value() /= other;
      return *this;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector<T>& point) noexcept {
      setVec2Value(glm::rotate((getVec2Value() - point.getVec2Value()), glm::radians(angleRotationValue)) + point.getVec2Value());
    }

    bool epsilonEquals(const GeoVector<T>& other, const GeoVector<T>& epsilonValue) const noexcept {
      return glm::all(glm::equal(getVec2Value(), other.getVec2Value(), epsilonValue.getVec2Value()));
    }

    static const GeoVector<T> zero() {
      return GeoVector<T>(0, 0);
    }

    static const GeoVector<T> one() {
      return GeoVector<T>(1, 1);
    }
  };
}

#endif //!NOVELRT_MATHS_GEOVECTOR_H
