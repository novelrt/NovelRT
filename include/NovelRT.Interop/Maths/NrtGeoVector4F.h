// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H

#include "NrtGeoVector2F.h"
#include "NrtGeoVector3F.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    float x;
    float y;
    float z;
    float w;
  } NrtGeoVector4F;

  NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector2F(NrtGeoVector2F vector);
  NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector3F(NrtGeoVector3F vector);
  int32_t Nrt_GeoVector4F_isNaN(NrtGeoVector4F vector);
  NrtGeoVector4F Nrt_GeoVector4F_uniform(float value);
  NrtGeoVector4F Nrt_GeoVector4F_zero();
  NrtGeoVector4F Nrt_GeoVector4F_one();
  int32_t Nrt_GeoVector4F_rotateToAngleAroundPoint(NrtGeoVector4F* const vector, float angleRotationValue, NrtGeoVector3F point);
  int32_t Nrt_GeoVector4F_epsilonEquals(NrtGeoVector4F vector, NrtGeoVector4F other, NrtGeoVector4F epsilonValue);
  NrtGeoVector4F Nrt_GeoVector4F_getNormalised(NrtGeoVector4F vector);
  float Nrt_GeoVector4F_getLength(NrtGeoVector4F vector);
  float Nrt_GeoVector4F_getMagnitude(NrtGeoVector4F vector);
  int32_t Nrt_GeoVector4F_equal(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_notEqual(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_lessThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_lessThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_greaterThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_greaterThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_addVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_subtractVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_multiplyVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_divideVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_addFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_subtractFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_multiplyFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_divideFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult);
  int32_t Nrt_GeoVector4F_addAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_subtractAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_multiplyAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_divideAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
  int32_t Nrt_GeoVector4F_addAssignFloat(NrtGeoVector4F* lhs, float rhs);
  int32_t Nrt_GeoVector4F_subtractAssignFloat(NrtGeoVector4F* lhs, float rhs);
  int32_t Nrt_GeoVector4F_multiplyAssignFloat(NrtGeoVector4F* lhs, float rhs);
  int32_t Nrt_GeoVector4F_divideAssignFloat(NrtGeoVector4F* lhs, float rhs);
  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
