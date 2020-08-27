// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR4_H
#define NOVELRT_MATHS_GEOVECTOR4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

#include "GeoVector4FStruct.h"

namespace NovelRT::Maths {
  class GeoVector4F : public NovelRTGeoVector4F {
    friend class Input::InteractionService;
    friend class GeoMatrix4x4F;

  private:
    GeoVector4F(glm::vec4 value) : NovelRTGeoVector4F { value.x, value.y, value.z, value.w } {}

    const glm::vec4& vec4Value() const {
      return reinterpret_cast<const glm::vec4&>(*this);
    }

    glm::vec4& vec4Value() {
      return reinterpret_cast<glm::vec4&>(*this);
    }

  public:
    GeoVector4F() {}
    GeoVector4F(float x, float y, float z, float w) : NovelRTGeoVector4F { x, y, z, w } {}
    GeoVector4F(const GeoVector2F& vec2Value) : NovelRTGeoVector4F { vec2Value.x, vec2Value.y, 0.0f, 0.0f } {}
    GeoVector4F(const GeoVector3F& vec3Value) : NovelRTGeoVector4F { vec3Value.x, vec3Value.y, vec3Value.z, 0.0f } {}

    float getX() const {
      return vec4Value().x;
    }

    void setX(float value) {
      vec4Value().x = value;
    }

    float getY() const {
      return vec4Value().y;
    }

    void setY(float value) {
      vec4Value().y = value;
    }

    float getZ() const {
      return vec4Value().z;
    }

    void setZ(float value) {
      vec4Value().z = value;
    }

    float getW() const {
      return vec4Value().w;
    }

    void setW(float value) {
      vec4Value().w = value;
    }

    inline GeoVector4F getNormalised() const noexcept {
      return GeoVector4F(glm::normalize(vec4Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(vec4Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector4F& other) const {
      return vec4Value() == other.vec4Value();
    }

    inline bool operator!=(const GeoVector4F& other) const {
      return vec4Value() != other.vec4Value();
    }

    inline bool operator<(const GeoVector4F& other) const {
      return glm::any(glm::lessThan(vec4Value(), other.vec4Value()));
    }

    inline bool operator<=(const GeoVector4F& other) const {
      return glm::any(glm::lessThanEqual(vec4Value(), other.vec4Value()));
    }

    inline bool operator>(const GeoVector4F& other) const {
      return glm::any(glm::greaterThan(vec4Value(), other.vec4Value()));
    }

    inline bool operator>=(const GeoVector4F& other) const {
      return glm::any(glm::greaterThanEqual(vec4Value(), other.vec4Value()));
    }

    inline GeoVector4F operator+(const GeoVector4F& other) const {
      return GeoVector4F(vec4Value() + other.vec4Value());
    }

    inline GeoVector4F operator-(const GeoVector4F& other) const {
      return GeoVector4F(vec4Value() - other.vec4Value());
    }

    inline GeoVector4F operator*(const GeoVector4F& other) const {
      return GeoVector4F(vec4Value() * other.vec4Value());
    }

    GeoVector4F operator/(const GeoVector4F& other) const {
      return GeoVector4F(vec4Value() / other.vec4Value());
    }

    inline GeoVector4F operator+(float other) const {
      return GeoVector4F(vec4Value() + other);
    }

    inline GeoVector4F operator-(float other) const {
      return GeoVector4F(vec4Value() - other);
    }

    inline GeoVector4F operator*(float other) const {
      return GeoVector4F(vec4Value() * other);
    }

    GeoVector4F operator/(float other) const {
      return GeoVector4F(vec4Value() / other);
    }

    inline GeoVector4F& operator+=(const GeoVector4F& other) {
      vec4Value() += other.vec4Value();
      return *this;
    }

    inline GeoVector4F& operator-=(const GeoVector4F& other) {
      vec4Value() -= other.vec4Value();
      return *this;
    }

    inline GeoVector4F operator*=(const GeoVector4F& other) {
      vec4Value() *= other.vec4Value();
      return *this;
    }

    GeoVector4F operator/=(const GeoVector4F& other) {
      vec4Value() /= other.vec4Value();
      return *this;
    }

    inline GeoVector4F operator+=(float other) {
      vec4Value() += other;
      return *this;
    }

    inline GeoVector4F operator-=(float other) {
      vec4Value() -= other;
      return *this;
    }

    inline GeoVector4F operator*=(float other) {
      vec4Value() *= other;
      return *this;
    }

    GeoVector4F operator/=(float other) {
      vec4Value() /= other;
      return *this;
    }

    void rotateToAngleAroundPoint(float angleRotationValue, const GeoVector4F& point, const GeoVector3F& axis = GeoVector3F(0, 0, 1)) noexcept {
      vec4Value() = glm::rotate((vec4Value() - point.vec4Value()), glm::radians(angleRotationValue), axis.vec3Value()) + point.vec4Value();
    }

    bool epsilonEquals(const GeoVector4F& other, const GeoVector4F& epsilonValue) const noexcept {
      return glm::all(glm::equal(vec4Value(), other.vec4Value(), epsilonValue.vec4Value()));
    }

    static const GeoVector4F zero() {
      return GeoVector4F::uniform(0);
    }

    static const GeoVector4F one() {
      return GeoVector4F::uniform(1);
    }

    static const GeoVector4F uniform(float value) {
      return GeoVector4F(value, value, value, value);
    }
  };

  inline GeoVector4F operator*(float lhs, const GeoVector4F& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR4_H
