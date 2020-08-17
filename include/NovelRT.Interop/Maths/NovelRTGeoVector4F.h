// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/Maths/NovelRTGeoVector3F.h"

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct
  {
    float x;
    float y;
    float z;
    float w;
  } NovelRTGeoVector4F;

  NovelRTGeoVector4F NovelRT_GeoVector4F_createFromGeoVector2F(NovelRTGeoVector2F vector);
  NovelRTGeoVector4F NovelRT_GeoVector4F_createFromGeoVector3F(NovelRTGeoVector3F vector);
  NovelRTBool NovelRT_GeoVector4F_isNaN(NovelRTGeoVector4F vector);
  NovelRTGeoVector4F NovelRT_GeoVector4F_uniform(float value);
  NovelRTGeoVector4F NovelRT_GeoVector4F_zero();
  NovelRTGeoVector4F NovelRT_GeoVector4F_one();
  NovelRTResult NovelRT_GeoVector4F_rotateToAngleAroundPoint(NovelRTGeoVector4F* const vector, float angleRotationValue, NovelRTGeoVector3F point, const char** errorMessage);
  NovelRTBool NovelRT_GeoVector4F_epsilonEquals(NovelRTGeoVector4F vector, NovelRTGeoVector4F other, NovelRTGeoVector4F epsilonValue);
  NovelRTGeoVector4F NovelRT_GeoVector4F_getNormalised(NovelRTGeoVector4F vector);
  float NovelRT_GeoVector4F_getLength(NovelRTGeoVector4F vector);
  float NovelRT_GeoVector4F_getMagnitude(NovelRTGeoVector4F vector);
  NovelRTBool NovelRT_GeoVector4F_equal(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs);
  NovelRTBool NovelRT_GeoVector4F_notEqual(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs);
  NovelRTBool NovelRT_GeoVector4F_lessThan(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs);
  NovelRTBool NovelRT_GeoVector4F_lessThanOrEqualTo(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs);
  NovelRTBool NovelRT_GeoVector4F_greaterThan(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs);
  NovelRTBool NovelRT_GeoVector4F_greaterThanOrEqualTo(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs);
  NovelRTResult NovelRT_GeoVector4F_addVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_subtractVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_multiplyVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_divideVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_addFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_subtractFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_multiplyFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_divideFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_addAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_subtractAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_multiplyAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_divideAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_addAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_subtractAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_multiplyAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector4F_divideAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage);
  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
