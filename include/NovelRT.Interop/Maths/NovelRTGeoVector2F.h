// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H

#include "../NovelRTInteropUtils.h"


#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    float x;
    float y;
  } NovelRTGeoVector2F;

  int32_t NovelRT_GeoVector2F_isNaN(NovelRTGeoVector2F vector);
  NovelRTGeoVector2F NovelRT_GeoVector2F_uniform(float value);
  NovelRTGeoVector2F NovelRT_GeoVector2F_zero();
  NovelRTGeoVector2F NovelRT_GeoVector2F_one();
  int32_t NovelRT_GeoVector2F_rotateToAngleAroundPoint(NovelRTGeoVector2F* vector, float angleRotationValue, NovelRTGeoVector2F point);
  int32_t NovelRT_GeoVector2F_epsilonEquals(NovelRTGeoVector2F vector, NovelRTGeoVector2F other, NovelRTGeoVector2F epsilonValue);
  NovelRTGeoVector2F NovelRT_GeoVector2F_getNormalised(NovelRTGeoVector2F vector);
  float NovelRT_GeoVector2F_getLength(NovelRTGeoVector2F vector);
  float NovelRT_GeoVector2F_getMagnitude(NovelRTGeoVector2F vector);
  int32_t NovelRT_GeoVector2F_equal(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_notEqual(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_lessThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_lessThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_greaterThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_greaterThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_addVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_subtractVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_multiplyVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_divideVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_addFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_subtractFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_multiplyFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_divideFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult);
  int32_t NovelRT_GeoVector2F_addAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_subtractAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_multiplyAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_divideAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs);
  int32_t NovelRT_GeoVector2F_addAssignFloat(NovelRTGeoVector2F* lhs, float rhs);
  int32_t NovelRT_GeoVector2F_subtractAssignFloat(NovelRTGeoVector2F* lhs, float rhs);
  int32_t NovelRT_GeoVector2F_multiplyAssignFloat(NovelRTGeoVector2F* lhs, float rhs);
  int32_t NovelRT_GeoVector2F_divideAssignFloat(NovelRTGeoVector2F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
