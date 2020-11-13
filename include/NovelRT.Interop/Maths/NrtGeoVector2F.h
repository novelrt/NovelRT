// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H

#include "../NrtInteropUtils.h"


#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    float x;
    float y;
  } NrtGeoVector2F;

  NrtBool Nrt_GeoVector2F_isNaN(NrtGeoVector2F vector);
  NrtGeoVector2F Nrt_GeoVector2F_uniform(float value);
  NrtGeoVector2F Nrt_GeoVector2F_zero();
  NrtGeoVector2F Nrt_GeoVector2F_one();
  void Nrt_GeoVector2F_rotateToAngleAroundPoint(NrtGeoVector2F* vector, float angleRotationValue, NrtGeoVector2F point);
  NrtBool Nrt_GeoVector2F_epsilonEquals(NrtGeoVector2F vector, NrtGeoVector2F other, NrtGeoVector2F epsilonValue);
  NrtGeoVector2F Nrt_GeoVector2F_getNormalised(NrtGeoVector2F vector);
  float Nrt_GeoVector2F_getLength(NrtGeoVector2F vector);
  float Nrt_GeoVector2F_getMagnitude(NrtGeoVector2F vector);
  NrtBool Nrt_GeoVector2F_equal(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtBool Nrt_GeoVector2F_notEqual(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtBool Nrt_GeoVector2F_lessThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtBool Nrt_GeoVector2F_lessThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtBool Nrt_GeoVector2F_greaterThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtBool Nrt_GeoVector2F_greaterThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtGeoVector2F Nrt_GeoVector2F_addVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtGeoVector2F Nrt_GeoVector2F_subtractVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtGeoVector2F Nrt_GeoVector2F_multiplyVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtGeoVector2F Nrt_GeoVector2F_divideVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
  NrtGeoVector2F Nrt_GeoVector2F_addFloat(NrtGeoVector2F lhs, float rhs);
  NrtGeoVector2F Nrt_GeoVector2F_subtractFloat(NrtGeoVector2F lhs, float rhs);
  NrtGeoVector2F Nrt_GeoVector2F_multiplyFloat(NrtGeoVector2F lhs, float rhs);
  NrtGeoVector2F Nrt_GeoVector2F_divideFloat(NrtGeoVector2F lhs, float rhs);
  void Nrt_GeoVector2F_addAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
  void Nrt_GeoVector2F_subtractAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
  void Nrt_GeoVector2F_multiplyAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
  void Nrt_GeoVector2F_divideAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
  void Nrt_GeoVector2F_addAssignFloat(NrtGeoVector2F* lhs, float rhs);
  void Nrt_GeoVector2F_subtractAssignFloat(NrtGeoVector2F* lhs, float rhs);
  void Nrt_GeoVector2F_multiplyAssignFloat(NrtGeoVector2F* lhs, float rhs);
  void Nrt_GeoVector2F_divideAssignFloat(NrtGeoVector2F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
