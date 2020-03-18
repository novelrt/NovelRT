// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR3_H
#define NOVELRT_MATHS_GEOVECTOR3_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template<typename T>
  class GeoVector3 {
    friend class Graphics::RenderObject;
    friend class Input::InteractionService;
    friend class GeoBounds;
    template<typename U>
    friend class GeoMatrix4;
    template<typename V>
    friend class GeoVector4;

  private:
    GeoVector3(glm::vec<3, T> value) : _value(glm::vec<4, T>(value, 0)) {}
    GeoVector3(glm::vec<4, T> value) : _value(value) {}

    inline glm::vec<3, T> getVec3Value() const {
      return glm::vec<3, T>(_value.x, _value.y, _value.z);
    }

    inline void setVec3Value(glm::vec<3, T> value) {
      _value.x = value.x;
      _value.y = value.y;
      _value.z = value.z;
    }

    const glm::vec<4, T>& vec4Value() const {
      return _value;
    }

    glm::vec<4, T>& vec4Value() {
      return _value;
    }

    glm::vec<4, T> _value;

  public:
    GeoVector3() {}
    GeoVector3(T x, T y, T z) : _value(glm::vec<4, T>(x, y, z, 0)) {}

    T getX() const {
      return getVec3Value().x;
    }

    void setX(T value) {
      _value.x = value;
    }

    T getY() const {
      return getVec3Value().y;
    }

    void setY(T value) {
      _value.y = value;
    }

    T getZ() const {
      return getVec3Value().z;
    }

    void setZ(T value) {
      _value.z = value;
    }

    inline GeoVector3<T> getNormalised() const noexcept {
      return GeoVector3<T>(glm::normalize(getVec3Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(getVec3Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector3<T>& other) const {
      return getVec3Value() == other.getVec3Value();
    }

    inline bool operator!=(const GeoVector3<T>& other) const {
      return getVec3Value() != other.getVec3Value();
    }

    inline bool operator<(const GeoVector3<T>& other) const {
      return glm::any(glm::lessThan(getVec3Value(), other.getVec3Value()));
    }

    inline bool operator<=(const GeoVector3<T>& other) const {
      return glm::any(glm::lessThanEqual(getVec3Value(), other.getVec3Value()));
    }

    inline bool operator>(const GeoVector3<T>& other) const {
      return glm::any(glm::greaterThan(getVec3Value(), other.getVec3Value()));
    }

    inline bool operator>=(const GeoVector3<T>& other) const {
      return glm::any(glm::greaterThanEqual(getVec3Value(), other.getVec3Value()));
    }

    inline GeoVector3<T> operator+(const GeoVector3<T>& other) const {
      return GeoVector3<T>(getVec3Value() + other.getVec3Value());
    }

    inline GeoVector3<T> operator-(const GeoVector3<T>& other) const {
      return GeoVector3<T>(getVec3Value() - other.getVec3Value());
    }

    inline GeoVector3<T> operator*(const GeoVector3<T>& other) const {
      return GeoVector3<T>(getVec3Value() * other.getVec3Value());
    }

    GeoVector3<T> operator/(const GeoVector3<T>& other) const {
      return GeoVector3<T>(getVec3Value() / other.getVec3Value());
    }

    inline GeoVector3<T> operator+(T other) const {
      return GeoVector3<T>(getVec3Value() + other);
    }

    inline GeoVector3<T> operator-(T other) const {
      return GeoVector3<T>(getVec3Value() - other);
    }

    inline GeoVector3<T> operator*(T other) const {
      return GeoVector3<T>(getVec3Value() * other);
    }

    GeoVector3<T> operator/(T other) const {
      return GeoVector3<T>(getVec3Value() / other);
    }

    inline GeoVector3<T>& operator+=(const GeoVector3<T>& other) {
      setVec3Value(getVec3Value() + other.getVec3Value());
      return *this;
    }

    inline GeoVector3<T>& operator-=(const GeoVector3<T>& other) {
      setVec3Value(getVec3Value() - other.getVec3Value());
      return *this;
    }

    inline GeoVector3<T> operator*=(const GeoVector3<T>& other) {
      setVec3Value(getVec3Value() * other.getVec3Value());
      return *this;
    }

    GeoVector3<T> operator/=(const GeoVector3<T>& other) {
      setVec3Value(getVec3Value() / other.getVec3Value());
      return *this;
    }

    inline GeoVector3<T> operator+=(T other) {
      setVec3Value(getVec3Value() + other);
      return *this;
    }

    inline GeoVector3<T> operator-=(T other) {
      setVec3Value(getVec3Value() - other);
      return *this;
    }

    inline GeoVector3<T> operator*=(T other) {
      setVec3Value(getVec3Value() * other);
      return *this;
    }

    GeoVector3<T> operator/=(T other) {
      setVec3Value(getVec3Value() / other);
      return *this;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector3<T>& point, const GeoVector3<T>& axis = GeoVector3<T>(0, 0, 1)) noexcept {
      setVec3Value(glm::rotate((getVec3Value() - point.getVec3Value()), glm::radians(angleRotationValue), axis.getVec3Value()) + point.getVec3Value());
    }

    bool epsilonEquals(const GeoVector3<T>& other, const GeoVector3<T>& epsilonValue) const noexcept {
      return glm::all(glm::equal(getVec3Value(), other.getVec3Value(), epsilonValue.getVec3Value()));
    }

    static const GeoVector3<T> zero() {
      return GeoVector3<T>(0, 0, 0);
    }

    static const GeoVector3<T> one() {
      return GeoVector3<T>(1, 1, 1);
    }
  };

  template<typename T>
  inline GeoVector3<T> operator*(T lhs, const GeoVector3<T>& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR3_H
