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
  NovelRTGeoVector4F NovelRT_GeoVector4F_createFromGeoVector3F(NovelRTGeoGector3F vector);
  NovelRTBool NovelRT_GeoVector3F_isNaN(NovelRTGeoVector4F vector);
  NovelRTGeoVector4F NovelRT_GeoVector3F_uniform(float value);
  NovelRTGeoVector4F NovelRT_GeoVector3F_zero();
  NovelRTGeoVector4F NovelRT_GeoVector3F_one();
  NovelRTResult NovelRT_GeoVector3F_rotateToAngleAroundPoint(NovelRTGeoVector4F* const vector, float angleRotationValue, NovelRTGeoVector3F point, const char** errorMessage);
  NovelRTBool NovelRT_GeoVector3F_epsilonEquals(NovelRTGeoVector4F vector, NovelRTGeoVector4F other, NovelRTGeoVector3F epsilonValue);
  NovelRTGeoVector3F NovelRT_GeoVector3F_getNormalised(NovelRTGeoVector3F vector);
  float NovelRT_GeoVector3F_getLength(NovelRTGeoVector3F vector);
  float NovelRT_GeoVector3F_getMagnitude(NovelRTGeoVector3F vector);
  NovelRTBool NovelRT_GeoVector3F_equal(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  NovelRTBool NovelRT_GeoVector3F_notEqual(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  NovelRTBool NovelRT_GeoVector3F_lessThan(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  NovelRTBool NovelRT_GeoVector3F_lessThanOrEqualTo(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  NovelRTBool NovelRT_GeoVector3F_greaterThan(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  NovelRTBool NovelRT_GeoVector3F_greaterThanOrEqualTo(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs);
  NovelRTResult NovelRT_GeoVector3F_addVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_subtractVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_multiplyVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_divideVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_addFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_subtractFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_multiplyFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_divideFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* const outputResult, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_addAssignVector(NovelRTGeoVector3F* const lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_subtractAssignVector(NovelRTGeoVector3F* const lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_multiplyAssignVector(NovelRTGeoVector3F* const lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_divideAssignVector(NovelRTGeoVector3F* const lhs, NovelRTGeoVector3F rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_addAssignFloat(NovelRTGeoVector3F* const lhs, float rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_subtractAssignFloat(NovelRTGeoVector3F* const lhs, float rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_multiplyAssignFloat(NovelRTGeoVector3F* const lhs, float rhs, const char** errorMessage);
  NovelRTResult NovelRT_GeoVector3F_divideAssignFloat(NovelRTGeoVector3F* const lhs, float rhs, const char** errorMessage);
  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
