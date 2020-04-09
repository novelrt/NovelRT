// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "GeoVector2F_t.h"
#include "GeoVector3F_t.h"

#ifndef NOVELRT_MATHS_GEOVECTOR4F_T_H
#define NOVELRT_MATHS_GEOVECTOR4F_T_H

#ifdef __cplusplus
extern "C" {
#endif

  struct GeoVector4F {
    float x;
    float y;
    float z;
    float w;
  };

  typedef struct GeoVector4F GeoVector4F_t;
  
  inline GeoVector4F_t GeoVector4F_create(float x, float y, float z, float w) {
    return { x, y, z, w };
  }

  inline GeoVector4F_t GeoVector4F_createFromGeoVector2F(const GeoVector2F_t& vector) {
    return { vector.getX(), vector.getY(), 0.0f, 0.0f };
  }

  inline GeoVector4F_t GeoVector4F_createFromGeoVector3F(const GeoVector3F_t& vector) {
    return { vector.x, vector.y, vector.z, 0.0f };
  }

  inline const GeoVector4F_t GeoVector4F_uniform(float value) {
    return GeoVector4F_create(value, value, value, value);
  }

  inline const GeoVector4F_t GeoVector4F_zero() {
    return GeoVector4F_uniform(0.0f);
  }

  inline const GeoVector4F_t GeoVector4F_one() {
    return GeoVector4F_uniform(1.0f);
  }

  inline float GeoVector4F_getX(GeoVector4F_t& gv) {
    return gv.x;
  }

  inline void GeoVector4F_setX(GeoVector4F_t& gv, float value) {
    gv.x = value;
  }

  inline float GeoVector4F_getY(GeoVector4F_t& gv) {
    return gv.y;
  }

  inline void GeoVector4F_setY(GeoVector4F_t& gv, float value) {
    gv.y = value;
  }

  inline float GeoVector4F_getZ(GeoVector4F_t& gv) {
    return gv.z;
  }

  inline void GeoVector4F_setZ(GeoVector4F_t& gv, float value) {
    gv.z = value;
  }

  inline float GeoVector4F_getW(GeoVector4F_t& gv) {
    return gv.w;
  }

  inline void GeoVector4F_setW(GeoVector4F_t& gv, float value) {
    gv.w = value;
  }

  inline void GeoVector4F_rotateToAngleAroundPoint(float angleRotationValue, GeoVector4F_t& vector, const GeoVector3F_t& point) noexcept {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w);
    geo.rotateToAngleAroundPoint(angleRotationValue, NovelRT::Maths::GeoVector3<float>(point.x, point.y, point.z));
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
  }

  inline bool GeoVector4F_epsilonEquals(GeoVector4F_t& vector, const GeoVector4F_t& other, const GeoVector4F_t& epsilonValue) noexcept {
    NovelRT::Maths::GeoVector4<float>v1 = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w);
    NovelRT::Maths::GeoVector4<float>v2 = NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    NovelRT::Maths::GeoVector4<float>v3 = NovelRT::Maths::GeoVector4<float>(epsilonValue.x, epsilonValue.y, epsilonValue.z, epsilonValue.w);
    return v1.epsilonEquals(v2, v3);
  }

  inline GeoVector4F_t GeoVector4F_getNormalised(GeoVector4F_t& gv) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(gv.x, gv.y, gv.z, gv.w).getNormalised();
    return { geo.getX(), geo.getY(), geo.getZ(), geo.getW() };
  }

  inline float GeoVector4F_getLength(GeoVector4F_t& gv) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(gv.x, gv.y, gv.z, gv.w);
    return geo.getLength();
  }

  inline float GeoVector4F_getMagnitude(GeoVector4F_t& gv) {
    return GeoVector4F_getLength(gv);
  }

  inline bool GeoVector4F_equal(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    return NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w) == NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
  }

  inline bool GeoVector4F_notEqual(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    return NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w) != NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
  }

  inline bool GeoVector4F_lessThan(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    return NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w) < NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
  }

  inline bool GeoVector4F_lessThanOrEqualTo(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    return NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w) <= NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
  }

  inline bool GeoVector4F_greaterThan(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    return NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w) > NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
  }

  inline bool GeoVector4F_greaterThanOrEqualTo(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    return NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w) >= NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
  }

  inline GeoVector4F_t GeoVector4F_addVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w)
      + NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_subtractVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w)
      - NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_multiplyVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w)
      * NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_divideVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w)
      / NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_addFloat(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w) + value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_subtractFloat(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w) - value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_multiplyFloat(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w) * value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_divideFloat(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w) / value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_addIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w);
    geo += NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_subtractFromVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w);
    geo -= NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_multiplyIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w);
    geo *= NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_divideIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(first.x, first.y, first.z, first.w);
    geo /= NovelRT::Maths::GeoVector4<float>(other.x, other.y, other.z, other.w);
    first.x = geo.getX();
    first.y = geo.getY();
    first.z = geo.getZ();
    first.w = geo.getW();
    return first;
  }

  inline GeoVector4F_t GeoVector4F_addFloatIntoVector(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w);
    geo += value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_subFloatFromVector(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w);
    geo -= value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_multiplyFloatIntoVector(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w);
    geo *= value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_divideFloatIntoVector(GeoVector4F_t& vector, float value) {
    NovelRT::Maths::GeoVector4<float> geo = NovelRT::Maths::GeoVector4<float>(vector.x, vector.y, vector.z, vector.w);
    geo /= value;
    vector.x = geo.getX();
    vector.y = geo.getY();
    vector.z = geo.getZ();
    vector.w = geo.getW();
    return vector;
  }

  inline GeoVector4F_t GeoVector4F_multiplyFloatIntoVectorInverse(float lhs, GeoVector4F& rhs) {
    return GeoVector4F_multiplyFloat(rhs, lhs);
  }
  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOVECTOR4F_T_H
