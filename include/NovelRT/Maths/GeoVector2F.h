// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR2_H
#define NOVELRT_MATHS_GEOVECTOR2_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

#include "BaseGeoVector2F.h"

namespace NovelRT::Maths {
  class GeoVector2F : public NovelRTGeoVector2F {
    friend class Graphics::RenderObject;
    friend class Input::InteractionService;
    friend class GeoVector3F;
    friend class GeoVector4F;

  private:

    GeoVector2F(glm::vec2 value) : NovelRTGeoVector2F { value.x, value.y } {}

    const glm::vec2& vec2Value() const {
      return reinterpret_cast<const glm::vec2&>(*this);
    }

    glm::vec2& vec2Value() {
      return reinterpret_cast<glm::vec2&>(*this);
    }

  public:
    GeoVector2F() : NovelRTGeoVector2F { 0.0f, 0.0f } {}
    GeoVector2F(float x, float y) : NovelRTGeoVector2F { x, y } {}

    float getX() const {
      return vec2Value().x;
    }

    void setX(float value) {
      vec2Value().x = value;
    }

    float getY() const {
      return vec2Value().y;
    }

    void setY(float value) {
      vec2Value().y = value;
    }

    inline GeoVector2F getNormalised() const noexcept {
      return GeoVector2F(glm::normalize(vec2Value()));
    }

    inline float getMagnitude() const noexcept {
      return glm::length(vec2Value());
    }

    inline float getLength() const noexcept {
      return getMagnitude();
    }

    inline bool operator==(const GeoVector2F& other) const {
      return vec2Value() == other.vec2Value();
    }

    inline bool operator!=(const GeoVector2F& other) const {
      return vec2Value() != other.vec2Value();
    }

    inline bool operator<(const GeoVector2F& other) const {
      return glm::any(glm::lessThan(vec2Value(), other.vec2Value()));
    }

    inline bool operator<=(const GeoVector2F& other) const {
      return glm::any(glm::lessThanEqual(vec2Value(), other.vec2Value()));
    }

    inline bool operator>(const GeoVector2F& other) const {
      return glm::any(glm::greaterThan(vec2Value(), other.vec2Value()));
    }

    inline bool operator>=(const GeoVector2F& other) const {
      return glm::any(glm::greaterThanEqual(vec2Value(), other.vec2Value()));
    }

    inline GeoVector2F operator+(const GeoVector2F& other) const {
      return GeoVector2F(vec2Value() + other.vec2Value());
    }

    inline GeoVector2F operator-(const GeoVector2F& other) const {
      return GeoVector2F(vec2Value() - other.vec2Value());
    }

    inline GeoVector2F operator*(const GeoVector2F& other) const {
      return GeoVector2F(vec2Value() * other.vec2Value());
    }

    GeoVector2F operator/(const GeoVector2F& other) const {
      return GeoVector2F(vec2Value() / other.vec2Value());
    }

    inline GeoVector2F operator+(float other) const {
      return GeoVector2F(vec2Value() + other);
    }

    inline GeoVector2F operator-(float other) const {
      return GeoVector2F(vec2Value() - other);
    }

    inline GeoVector2F operator*(float other) const {
      return GeoVector2F(vec2Value() * other);
    }

    GeoVector2F operator/(float other) const {
      return GeoVector2F(vec2Value() / other);
    }

    inline GeoVector2F& operator+=(const GeoVector2F& other) {
      vec2Value() = vec2Value() + other.vec2Value();
      return *this;
    }

    inline GeoVector2F& operator-=(const GeoVector2F& other) {
      vec2Value() = vec2Value() - other.vec2Value();
      return *this;
    }

    inline GeoVector2F operator*=(const GeoVector2F& other) {
      vec2Value() = vec2Value() * other.vec2Value();
      return *this;
    }

    GeoVector2F operator/=(const GeoVector2F& other) {
      vec2Value() = vec2Value() / other.vec2Value();
      return *this;
    }

    inline GeoVector2F operator+=(float other) {
      vec2Value() = vec2Value() + other;
      return *this;
    }

    inline GeoVector2F operator-=(float other) {
      vec2Value() = vec2Value() - other;
      return *this;
    }

    inline GeoVector2F operator*=(float other) {
      vec2Value() = vec2Value() * other;
      return *this;
    }

    GeoVector2F operator/=(float other) {
      vec2Value() = vec2Value() / other;
      return *this;
    }

    void rotateToAngleAroundPoint(float angleRotationValue, const GeoVector2F& point) noexcept {
      vec2Value() = glm::rotate((vec2Value() - point.vec2Value()), glm::radians(angleRotationValue)) + point.vec2Value();
    }

    bool epsilonEquals(const GeoVector2F& other, const GeoVector2F& epsilonValue) const noexcept {
      return glm::all(glm::equal(vec2Value(), other.vec2Value(), epsilonValue.vec2Value()));
    }

    static const GeoVector2F zero() {
      return GeoVector2F::uniform(0);
    }

    static const GeoVector2F one() {
      return GeoVector2F::uniform(1);
    }

    static const GeoVector2F uniform(float value) {
      return GeoVector2F(value, value);
    }
  };

  inline GeoVector2F operator*(float lhs, const GeoVector2F& rhs) {
    return rhs * lhs;
  }
}

#endif //!NOVELRT_MATHS_GEOVECTOR2_H
