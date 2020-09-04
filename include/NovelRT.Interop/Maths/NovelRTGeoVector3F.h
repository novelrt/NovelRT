// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H

#include "NovelRTGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    float x;
    float y;
    float z;
  } NovelRTGeoVector3F;

  NovelRTGeoVector3F NovelRT_GeoVector3F_createFromGeoVector2F(NovelRTGeoVector2F vector);
  int32_t NovelRT_GeoVector3F_isNaN(NovelRTGeoVector3F vector);
  NovelRTGeoVector3F NovelRT_GeoVector3F_uniform(float value);
  NovelRTGeoVector3F NovelRT_GeoVector3F_zero();
  NovelRTGeoVector3F NovelRT_GeoVector3F_one();
  int32_t NovelRT_GeoVector3F_rotateToAngleAroundPoint(NovelRTGeoVector3F* vector, float angleRotationValue, NovelRTGeoVector3F point, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_epsilonEquals(NovelRTGeoVector3F vector, NovelRTGeoVector3F other, NovelRTGeoVector3F epsilonValue);
  NovelRTGeoVector3F NovelRT_GeoVector3F_getNormalised(NovelRTGeoVector3F vector);
  float NovelRT_GeoVector3F_getLength(NovelRTGeoVector3F vector);
  float NovelRT_GeoVector3F_getMagnitude(NovelRTGeoVector3F vector);
  int32_t NovelRT_GeoVector3F_equal(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  int32_t NovelRT_GeoVector3F_notEqual(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  int32_t NovelRT_GeoVector3F_lessThan(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  int32_t NovelRT_GeoVector3F_lessThanOrEqualTo(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  int32_t NovelRT_GeoVector3F_greaterThan(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  int32_t NovelRT_GeoVector3F_greaterThanOrEqualTo(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  int32_t NovelRT_GeoVector3F_addVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_subtractVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_multiplyVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_divideVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_addFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_subtractFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_multiplyFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_divideFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_addAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_subtractAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_multiplyAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_divideAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_addAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_subtractAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_multiplyAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage);
  int32_t NovelRT_GeoVector3F_divideAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
