// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "GeoVector2F_t.h"

#ifndef NOVELRT_MATHS_GEOVECTOR3F_H
#define NOVELRT_MATHS_GEOVECTOR3F_H

#ifdef __cplusplus
extern "C" {
#endif

 struct GeoVector3F {
   float x;
   float y;
   float z;
 };

typedef struct GeoVector3F GeoVector3F_t;

inline GeoVector3F_t GeoVector3F_create(float x, float y, float z) {
  return { x, y, z };
}

inline GeoVector3F_t GeoVector3F_createFromGeoVector2F(const GeoVector2F_t& vector) {
  return { vector.x, vector.y, 0.0f };
}

inline const GeoVector3F_t GeoVector3F_uniform(float value) {
  return GeoVector3F_create(value, value, value);
}

inline const GeoVector3F_t GeoVector3F_zero() {
  return GeoVector3F_uniform(0.0f);
}

inline const GeoVector3F_t GeoVector3F_one() {
  return GeoVector3F_uniform(1.0f);
}

inline float GeoVector3F_getX(GeoVector3F_t& gv) {
  return gv.x;
}

inline void GeoVector3F_setX(GeoVector3F_t& gv, float value) {
  gv.x = value;
}

inline float GeoVector3F_getY(GeoVector3F_t& gv) {
  return gv.y;
}

inline void GeoVector3F_setY(GeoVector3F_t& gv, float value) {
  gv.y = value;
}

inline float GeoVector3F_getZ(GeoVector3F_t& gv) {
  return gv.z;
}

inline void GeoVector3F_setZ(GeoVector3F_t& gv, float value) {
  gv.z = value;
}

inline void GeoVector3F_rotateToAngleAroundPoint(float angleRotationValue, GeoVector3F& vector, const GeoVector3F& point) noexcept {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z);
  geo.rotateToAngleAroundPoint(angleRotationValue, NovelRT::Maths::GeoVector3<float>(point.x, point.y, point.z));
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
}

inline bool GeoVector3F_epsilonEquals(GeoVector3F& vector, const GeoVector3F& other, const GeoVector3F& epsilonValue) noexcept {
  NovelRT::Maths::GeoVector3<float>v1 = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z);
  NovelRT::Maths::GeoVector3<float>v2 = NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  NovelRT::Maths::GeoVector3<float>v3 = NovelRT::Maths::GeoVector3<float>(epsilonValue.x, epsilonValue.y, epsilonValue.z);
  return v1.epsilonEquals(v2, v3);
}

inline GeoVector3F_t GeoVector3F_getNormalised(GeoVector3F_t& gv) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(gv.x, gv.y, gv.z).getNormalised();
  return { geo.getX(), geo.getY(), geo.getZ() };
}

inline float GeoVector3F_getLength(GeoVector3F_t& gv) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(gv.x, gv.y, gv.z);
  return geo.getLength();
}

inline float GeoVector3F_getMagnitude(GeoVector3F_t& gv) {
  return GeoVector3F_getLength(gv);
}

inline bool GeoVector3F_equal(const GeoVector3F_t& first, const GeoVector3F_t& other) {
  return NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z) == NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
}

inline bool GeoVector3F_notEqual(const GeoVector3F_t& first, const GeoVector3F_t& other) {
  return NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z) != NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
}

inline bool GeoVector3F_lessThan(const GeoVector3F_t& first, const GeoVector3F_t& other) {
  return NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z) < NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
}

inline bool GeoVector3F_lessThanOrEqualTo(const GeoVector3F_t& first, const GeoVector3F_t& other) {
  return NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z) <= NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
}

inline bool GeoVector3F_greaterThan(const GeoVector3F_t& first, const GeoVector3F_t& other) {
  return NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z) > NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
}

inline bool GeoVector3F_greaterThanOrEqualTo(const GeoVector3F_t& first, const GeoVector3F_t& other) {
  return NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z) >= NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
}

inline GeoVector3F_t GeoVector3F_addVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z)
    + NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_subtractVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z)
    - NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_multiplyVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z)
    * NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_divideVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo =  NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z)
    / NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_addFloat(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z) + value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_subtractFloat(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z) - value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_multiplyFloat(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z) * value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_divideFloat(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z) / value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_addIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z);
  geo += NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_subtractFromVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z);
  geo -= NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_multiplyIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo =NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z);
  geo *= NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_divideIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(first.x, first.y, first.z);
  geo /= NovelRT::Maths::GeoVector3<float>(other.x, other.y, other.z);
  first.x = geo.getX();
  first.y = geo.getY();
  first.z = geo.getZ();
  return first;
}

inline GeoVector3F_t GeoVector3F_addFloatIntoVector(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z);
  geo += value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_subFloatFromVector(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z);
  geo -= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_multiplyFloatIntoVector(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z);
  geo *= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_divideFloatIntoVector(GeoVector3F_t& vector, float value) {
  NovelRT::Maths::GeoVector3<float> geo = NovelRT::Maths::GeoVector3<float>(vector.x, vector.y, vector.z);
  geo /= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  vector.z = geo.getZ();
  return vector;
}

inline GeoVector3F_t GeoVector3F_multiplyFloatIntoVectorInverse(float lhs, GeoVector3F& rhs) {
  return GeoVector3F_multiplyFloat(rhs, lhs);
}

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOVECTOR3F_H
