// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtBool Nrt_GeoVector2F_IsNaN(NrtGeoVector2F vector);
    NrtGeoVector2F Nrt_GeoVector2F_Uniform(float value);
    NrtGeoVector2F Nrt_GeoVector2F_Zero();
    NrtGeoVector2F Nrt_GeoVector2F_One();
    void Nrt_GeoVector2F_RotateToAngleAroundPointDeg(NrtGeoVector2F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector2F point);
    void Nrt_GeoVector2F_RotateToAngleAroundPointRad(NrtGeoVector2F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector2F point);
    NrtBool Nrt_GeoVector2F_EpsilonEquals(NrtGeoVector2F vector, NrtGeoVector2F other, NrtGeoVector2F epsilonValue);
    NrtGeoVector2F Nrt_GeoVector2F_getNormalised(NrtGeoVector2F vector);
    float Nrt_GeoVector2F_GetLength(NrtGeoVector2F vector);
    float Nrt_GeoVector2F_GetMagnitude(NrtGeoVector2F vector);
    float Nrt_GeoVector2F_GetSquaredLength(NrtGeoVector2F vector);
    float Nrt_GeoVector2F_GetSquaredMagnitude(NrtGeoVector2F vector);
    float Nrt_GeoVector2F_Dot(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    float Nrt_GeoVector2F_Distance(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    float Nrt_GeoVector2F_SquaredDistance(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtBool Nrt_GeoVector2F_Equal(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtBool Nrt_GeoVector2F_NotEqual(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtBool Nrt_GeoVector2F_LessThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtBool Nrt_GeoVector2F_LessThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtBool Nrt_GeoVector2F_GreaterThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtBool Nrt_GeoVector2F_GreaterThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtGeoVector2F Nrt_GeoVector2F_AddVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtGeoVector2F Nrt_GeoVector2F_SubtractVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtGeoVector2F Nrt_GeoVector2F_MultiplyVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtGeoVector2F Nrt_GeoVector2F_DivideVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);
    NrtGeoVector2F Nrt_GeoVector2F_AddFloat(NrtGeoVector2F lhs, float rhs);
    NrtGeoVector2F Nrt_GeoVector2F_SubtractFloat(NrtGeoVector2F lhs, float rhs);
    NrtGeoVector2F Nrt_GeoVector2F_MultiplyFloat(NrtGeoVector2F lhs, float rhs);
    NrtGeoVector2F Nrt_GeoVector2F_DivideFloat(NrtGeoVector2F lhs, float rhs);
    void Nrt_GeoVector2F_AddAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
    void Nrt_GeoVector2F_SubtractAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
    void Nrt_GeoVector2F_MultiplyAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
    void Nrt_GeoVector2F_DivideAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);
    void Nrt_GeoVector2F_AddAssignFloat(NrtGeoVector2F* lhs, float rhs);
    void Nrt_GeoVector2F_SubtractAssignFloat(NrtGeoVector2F* lhs, float rhs);
    void Nrt_GeoVector2F_MultiplyAssignFloat(NrtGeoVector2F* lhs, float rhs);
    void Nrt_GeoVector2F_DivideAssignFloat(NrtGeoVector2F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
