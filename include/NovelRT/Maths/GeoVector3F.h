// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR3_H
#define NOVELRT_MATHS_GEOVECTOR3_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class GeoVector3F {
    friend class Input::InteractionService;
    friend class GeoVector4F;

  private:
    glm::vec3 _value;

    GeoVector3F(glm::vec3 value) : _value(value) {}

    const glm::vec3& vec3Value() const {
      return _value;
    }

    glm::vec3& vec3Value() {
      return _value;
    }

  public:
    GeoVector3F() {}
    GeoVector3F(float x, float y, float z) : _value(glm::vec4(x, y, z, 0)) {}
    GeoVector3F(const GeoVector2F& vec2Value) : _value(vec2Value.vec2Value(), 0) {}

    float getX() const {
      return vec3Value().x;
    }

    void setX(float value) {
      vec3Value().x = value;
    }

    float getY() const {
      return vec3Value().y;
    }

    void setY(float value) {
      vec3Value().y = value;
    }

    float getZ() const {
      return vec3Value().z;
    }

    void setZ(float value) {
      vec3Value().z = value;
    }

    inline GeoVector3F getNormalised() const noexcept {
      return GeoVector3F(glm::normalize(vec3Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(vec3Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector3F& other) const {
      return vec3Value() == other.vec3Value();
    }

    inline bool operator!=(const GeoVector3F& other) const {
      return vec3Value() != other.vec3Value();
    }

    inline bool operator<(const GeoVector3F& other) const {
      return glm::any(glm::lessThan(vec3Value(), other.vec3Value()));
    }

    inline bool operator<=(const GeoVector3F& other) const {
      return glm::any(glm::lessThanEqual(vec3Value(), other.vec3Value()));
    }

    inline bool operator>(const GeoVector3F& other) const {
      return glm::any(glm::greaterThan(vec3Value(), other.vec3Value()));
    }

    inline bool operator>=(const GeoVector3F& other) const {
      return glm::any(glm::greaterThanEqual(vec3Value(), other.vec3Value()));
    }

    inline GeoVector3F operator+(const GeoVector3F& other) const {
      return GeoVector3F(vec3Value() + other.vec3Value());
    }

    inline GeoVector3F operator-(const GeoVector3F& other) const {
      return GeoVector3F(vec3Value() - other.vec3Value());
    }

    inline GeoVector3F operator*(const GeoVector3F& other) const {
      return GeoVector3F(vec3Value() * other.vec3Value());
    }

    GeoVector3F operator/(const GeoVector3F& other) const {
      return GeoVector3F(vec3Value() / other.vec3Value());
    }

    inline GeoVector3F operator+(float other) const {
      return GeoVector3F(vec3Value() + other);
    }

    inline GeoVector3F operator-(float other) const {
      return GeoVector3F(vec3Value() - other);
    }

    inline GeoVector3F operator*(float other) const {
      return GeoVector3F(vec3Value() * other);
    }

    GeoVector3F operator/(float other) const {
      return GeoVector3F(vec3Value() / other);
    }

    inline GeoVector3F& operator+=(const GeoVector3F& other) {
      vec3Value() = vec3Value() + other.vec3Value();
      return *this;
    }

    inline GeoVector3F& operator-=(const GeoVector3F& other) {
      vec3Value() = vec3Value() - other.vec3Value();
      return *this;
    }

    inline GeoVector3F operator*=(const GeoVector3F& other) {
      vec3Value() = vec3Value() * other.vec3Value();
      return *this;
    }

    GeoVector3F operator/=(const GeoVector3F& other) {
      vec3Value() = vec3Value() / other.vec3Value();
      return *this;
    }

    inline GeoVector3F operator+=(float other) {
      vec3Value() = vec3Value() + other;
      return *this;
    }

    inline GeoVector3F operator-=(float other) {
      vec3Value() = vec3Value() - other;
      return *this;
    }

    inline GeoVector3F operator*=(float other) {
      vec3Value() = vec3Value() * other;
      return *this;
    }

    GeoVector3F operator/=(float other) {
      vec3Value() = vec3Value() / other;
      return *this;
    }

    void rotateToAngleAroundPoint(float angleRotationValue, const GeoVector3F& point, const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept {
      vec3Value() = glm::rotate((vec3Value() - point.vec3Value()), glm::radians(angleRotationValue), axis.vec3Value()) + point.vec3Value();
    }

    bool epsilonEquals(const GeoVector3F& other, const GeoVector3F& epsilonValue) const noexcept {
      return glm::all(glm::equal(vec3Value(), other.vec3Value(), epsilonValue.vec3Value()));
    }

    static const GeoVector3F zero() {
      return GeoVector3F::uniform(0);
    }

    static const GeoVector3F one() {
      return GeoVector3F::uniform(1);
    }

    static const GeoVector3F uniform(float value) {
      return GeoVector3F(value, value, value);
    }
  };

  inline GeoVector3F operator*(float lhs, const GeoVector3F& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR3_H
