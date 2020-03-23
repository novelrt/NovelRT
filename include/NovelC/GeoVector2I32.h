// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"


#ifndef NOVELRT_MATHS_GEOVECTOR2I32_H
#define NOVELRT_MATHS_GEOVECTOR2I32_H

#ifdef __cplusplus
extern "C" {
#endif

 struct GeoVector2I32 {
   int32_t x;
   int32_t y;
 };

typedef struct GeoVector2I32 GeoVector2I32_t;

GeoVector2I32_t GeoVector2I32_create(int32_t x, int32_t y) {
  GeoVector2I32_t gv = { x, y };
  return gv;
}

inline const GeoVector2I32_t GeoVector2I32_uniform(int32_t value) {
  return GeoVector2I32_create(value, value);
}

inline const GeoVector2I32_t GeoVector2I32_zero() {
  return GeoVector2I32_uniform(0);
}

inline const GeoVector2I32_t GeoVector2I32_one() {
  return GeoVector2I32_uniform(1);
}

int32_t GeoVector2I32_getX(GeoVector2I32_t& gv) {
  return gv.x;
}

void GeoVector2I32_setX(GeoVector2I32_t& gv, int32_t value) {
  gv.x = value;
}

int32_t GeoVector2I32_getY(GeoVector2I32_t& gv) {
  return gv.y;
}

void GeoVector2I32_setY(GeoVector2I32_t& gv, int32_t value) {
  gv.y = value;
}

//glm::radians only accepts floating-point input
void GeoVector2I32_rotateToAngleAroundPoint(GeoVector2I32& vector, float angleRotationValue, const GeoVector2I32& point) noexcept {
  NovelRT::Maths::GeoVector2<float> geo = NovelRT::Maths::GeoVector2<float>(static_cast<float>(vector.x), static_cast<float>(vector.y));
  geo.rotateToAngleAroundPoint(angleRotationValue, NovelRT::Maths::GeoVector2<float>(static_cast<float>(point.x), static_cast<float>(point.y)));
  vector.x = static_cast<int32_t>(geo.getX());
  vector.y = static_cast<int32_t>(geo.getY());
}

bool GeoVector2I32_epsilonEquals(GeoVector2I32& vector, const GeoVector2I32& other, const GeoVector2I32& epsilonValue) noexcept {
  NovelRT::Maths::GeoVector2<float>v1 = NovelRT::Maths::GeoVector2<float>(static_cast<float>(vector.x), static_cast<float>(vector.y));
  NovelRT::Maths::GeoVector2<float>v2 = NovelRT::Maths::GeoVector2<float>(static_cast<float>(other.x), static_cast<float>(other.y));
  NovelRT::Maths::GeoVector2<float>v3 = NovelRT::Maths::GeoVector2<float>(static_cast<float>(epsilonValue.x), static_cast<float>(epsilonValue.y));
  return v1.epsilonEquals(v2, v3);
}

inline GeoVector2I32_t GeoVector2I32_getNormalised(GeoVector2I32_t& gv) {
  NovelRT::Maths::GeoVector2<float> geo = NovelRT::Maths::GeoVector2<float>(static_cast<float>(gv.x), static_cast<float>(gv.y)).getNormalised();
  GeoVector2I32_t normal = {static_cast<int32_t>(geo.getX()), static_cast<int32_t>(geo.getY())};
  return normal;
}

inline float GeoVector2I32_getLength(GeoVector2I32_t& gv) {
  NovelRT::Maths::GeoVector2<float> geo = NovelRT::Maths::GeoVector2<float>(static_cast<float>(gv.x), static_cast<float>(gv.y));
  return geo.getLength();
}

inline float GeoVector2I32_getMagnitude(GeoVector2I32_t& gv) {
  return GeoVector2I32_getLength(gv);
}

inline bool GeoVector2I32_equal(const GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  return NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) == NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
}

inline bool GeoVector2I32_notEqual(const GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  return NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) != NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
}

inline bool GeoVector2I32_lessThan(const GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  return NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) < NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
}

inline bool GeoVector2I32_lessThanOrEqualTo(const GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  return NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) <= NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
}

inline bool GeoVector2I32_greaterThan(const GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  return NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) > NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
}

inline bool GeoVector2I32_greaterThanOrEqualTo(const GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  return NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) >= NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
}

inline GeoVector2I32_t GeoVector2I32_addVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x,first.y) + NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_subtractVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) - NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_multiplyVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) * NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_divideVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y) / NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_addI32(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y) + value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_subtractI32(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y) - value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_multiplyI32(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y) * value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

GeoVector2I32_t GeoVector2I32_divideI32(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y) / value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_addIntoVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y);
  geo += NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_subtractFromVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y);
  geo -= NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_multiplyIntoVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y);
  geo *= NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

GeoVector2I32_t GeoVector2I32_divideIntoVector(GeoVector2I32_t& first, const GeoVector2I32_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(first.x, first.y);
  geo /= NovelRT::Maths::GeoVector2<int32_t>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2I32_t GeoVector2I32_addI32IntoVector(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y);
  geo += value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_subI32FromVector(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y);
  geo -= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_multiplyI32IntoVector(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y);
  geo *= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_divideI32IntoVector(GeoVector2I32_t& vector, int32_t value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<int32_t>(vector.x, vector.y);
  geo /= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2I32_t GeoVector2I32_multiplyI32IntoVectorInverse(int32_t lhs, GeoVector2I32& rhs) {
  return GeoVector2I32_multiplyI32(rhs, lhs);
}

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GeoVector2I32_H
