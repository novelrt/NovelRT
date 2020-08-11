// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"
#include "NovelRT.Interop/Maths/GeoVector3F_t.h"

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H

#ifdef __cplusplus
extern "C" {
#endif

  struct GeoVector4F_t
  {
    float x;
    float y;
    float z;
    float w;
  };

  GeoVector4F_t GeoVector4F_create(float x, float y, float z, float w);
  GeoVector4F_t GeoVector4F_createFromGeoVector2F(const GeoVector2F_t& vector);
  GeoVector4F_t GeoVector4F_createFromGeoVector3F(const GeoVector3F_t& vector);
  const GeoVector4F_t GeoVector4F_uniform(float value);
  const GeoVector4F_t GeoVector4F_zero();
  const GeoVector4F_t GeoVector4F_one();
  float GeoVector4F_getX(GeoVector4F_t& gv);
  void GeoVector4F_setX(GeoVector4F_t& gv, float value);
  float GeoVector4F_getY(GeoVector4F_t& gv);
  void GeoVector4F_setY(GeoVector4F_t& gv, float value);
  float GeoVector4F_getZ(GeoVector4F_t& gv);
  void GeoVector4F_setZ(GeoVector4F_t& gv, float value);
  float GeoVector4F_getW(GeoVector4F_t& gv);
  void GeoVector4F_setW(GeoVector4F_t& gv, float value);
  void GeoVector4F_rotateToAngleAroundPoint(GeoVector4F_t& vector, float angleRotationValue, const GeoVector3F_t& point) noexcept; 
  bool GeoVector4F_epsilonEquals(const GeoVector4F_t& vector, const GeoVector4F_t& other, const GeoVector4F_t& epsilonValue) noexcept;
  GeoVector4F_t GeoVector4F_getNormalised(const GeoVector4F_t& vector);
  float GeoVector4F_getLength(const GeoVector4F_t& vector);
  float GeoVector4F_getMagnitude(const GeoVector4F_t& vector);
  bool GeoVector4F_equal(const GeoVector4F_t& first, const GeoVector4F_t& other);
  bool GeoVector4F_notEqual(const GeoVector4F_t& first, const GeoVector4F_t& other);
  bool GeoVector4F_lessThan(const GeoVector4F_t& first, const GeoVector4F_t& other);
  bool GeoVector4F_lessThanOrEqualTo(const GeoVector4F_t& first, const GeoVector4F_t& other);
  bool GeoVector4F_greaterThan(const GeoVector4F_t& first, const GeoVector4F_t& other);
  bool GeoVector4F_greaterThanOrEqualTo(const GeoVector4F_t& first, const GeoVector4F_t& other);
  GeoVector4F_t GeoVector4F_addVector(const GeoVector4F_t& first, const GeoVector4F_t& other);
  GeoVector4F_t GeoVector4F_subtractVector(const GeoVector4F_t& first, const GeoVector4F_t& other);
  GeoVector4F_t GeoVector4F_multiplyVector(const GeoVector4F_t& first, const GeoVector4F_t& other);
  GeoVector4F_t GeoVector4F_divideVector(const GeoVector4F_t& first, const GeoVector4F_t& other);
  GeoVector4F_t GeoVector4F_addFloat(const GeoVector4F_t& vector, float value);
  GeoVector4F_t GeoVector4F_subtractFloat(const GeoVector4F_t& vector, float value);
  GeoVector4F_t GeoVector4F_multiplyFloat(const GeoVector4F_t& vector, float value);
  GeoVector4F_t GeoVector4F_divideFloat(const GeoVector4F_t& vector, float value);
  void GeoVector4F_addIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other);
  void GeoVector4F_subtractFromVector(GeoVector4F_t& first, const GeoVector4F_t& other);
  void GeoVector4F_multiplyIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other);
  void GeoVector4F_divideIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other);
  void GeoVector4F_addFloatIntoVector(GeoVector4F_t& vector, float value);
  void GeoVector4F_subFloatFromVector(GeoVector4F_t& vector, float value);
  void GeoVector4F_multiplyFloatIntoVector(GeoVector4F_t& vector, float value);
  void GeoVector4F_divideFloatIntoVector(GeoVector4F_t& vector, float value);
  GeoVector4F_t GeoVector4F_multiplyFloatInverse(float lhs, const GeoVector4F_t& rhs);
  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
