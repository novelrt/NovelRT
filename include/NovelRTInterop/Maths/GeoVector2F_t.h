// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"

#ifdef _WIN32
#pragma warning( disable: 4099 )
#pragma warning( disable: 4190 )
#endif

#ifndef NOVELRT_MATHS_GEOVECTOR2F_H
#define NOVELRT_MATHS_GEOVECTOR2F_H

#ifdef __cplusplus
extern "C" {
#endif

  using namespace NovelRT;

  typedef struct Maths::GeoVector2<float> GeoVector2F_t;

  inline GeoVector2F_t GeoVector2F_create(float x, float y) {
    GeoVector2F_t result = Maths::GeoVector2<float>(x, y);
    return result;
  }

  inline const GeoVector2F_t GeoVector2F_uniform(float value) {
    return Maths::GeoVector2<float>(value, value);
  }

  inline const GeoVector2F_t GeoVector2F_zero() {
    return GeoVector2F_uniform(0.0f);
  }

  inline const GeoVector2F_t GeoVector2F_one() {
    return GeoVector2F_uniform(1.0f);
  }

  inline float GeoVector2F_getX(GeoVector2F_t& gv) {
    return gv.getX();
  }

  inline void GeoVector2F_setX(GeoVector2F_t& gv, float value) {
    gv.setX(value);
  }

  inline float GeoVector2F_getY(GeoVector2F_t& gv) {
    return gv.getY();
  }

  inline void GeoVector2F_setY(GeoVector2F_t& gv, float value) {
    gv.setY(value);
  }

  inline void GeoVector2F_rotateToAngleAroundPoint(GeoVector2F_t& vector, float angleRotationValue, const GeoVector2F_t& point) noexcept {
    vector.rotateToAngleAroundPoint(angleRotationValue, point);
  }

  inline bool GeoVector2F_epsilonEquals(GeoVector2F_t& vector, const GeoVector2F_t& other, const GeoVector2F_t& epsilonValue) noexcept {
    return vector.epsilonEquals(other, epsilonValue);
  }

  inline GeoVector2F_t GeoVector2F_getNormalised(GeoVector2F_t& gv) {
    return gv.getNormalised();
  }

  inline float GeoVector2F_getLength(GeoVector2F_t& gv) {
    return gv.getLength();
  }

  inline float GeoVector2F_getMagnitude(GeoVector2F_t& gv) {
    return gv.getMagnitude();
  }

  inline bool GeoVector2F_equal(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first == other;
  }

  inline bool GeoVector2F_notEqual(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first != other;
  }

  inline bool GeoVector2F_lessThan(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first < other;
  }

  inline bool GeoVector2F_lessThanOrEqualTo(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first <= other;
  }

  inline bool GeoVector2F_greaterThan(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first > other;
  }

  inline bool GeoVector2F_greaterThanOrEqualTo(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first >= other;
  }

  inline GeoVector2F_t GeoVector2F_addVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float> result = first + other;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_subtractVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float> result = first - other;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_multiplyVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float> result = first * other;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_divideVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float> result = first / other;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_addFloat(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float> result = vector + value;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_subtractFloat(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float> result = vector - value;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_multiplyFloat(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float> result = vector * value;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_divideFloat(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float> result = vector / value;
    return result;
  }

  inline GeoVector2F_t GeoVector2F_addIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first += other;
  }

  inline GeoVector2F_t GeoVector2F_subtractFromVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first -= other;
  }

  inline GeoVector2F_t GeoVector2F_multiplyIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first *= other;
  }

  inline GeoVector2F_t GeoVector2F_divideIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    return first /= other;
  }

  inline GeoVector2F_t GeoVector2F_addFloatIntoVector(GeoVector2F_t& vector, float value) {
    return vector += value;
  }

  inline GeoVector2F_t GeoVector2F_subFloatFromVector(GeoVector2F_t& vector, float value) {
    return vector -= value;
  }

  inline GeoVector2F_t GeoVector2F_multiplyFloatIntoVector(GeoVector2F_t& vector, float value) {
    return vector *= value;
  }

  inline GeoVector2F_t GeoVector2F_divideFloatIntoVector(GeoVector2F_t& vector, float value) {
    return vector /= value;
  }

  inline GeoVector2F_t GeoVector2F_multiplyFloatInverse(float lhs, GeoVector2F_t& rhs) {
    return rhs * lhs;
  }

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOVECTOR2F_H
