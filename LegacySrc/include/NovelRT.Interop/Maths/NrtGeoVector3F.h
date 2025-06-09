// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H

#include "NrtGeoVector2F.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtGeoVector3F Nrt_GeoVector3F_CreateFromGeoVector2F(NrtGeoVector2F vector);
    NrtBool Nrt_GeoVector3F_IsNaN(NrtGeoVector3F vector);
    NrtGeoVector3F Nrt_GeoVector3F_Uniform(float value);
    NrtGeoVector3F Nrt_GeoVector3F_Zero();
    NrtGeoVector3F Nrt_GeoVector3F_One();
    void Nrt_GeoVector3F_RotateToAngleAroundPointDeg(NrtGeoVector3F* vector,
                                                     float angleRotationValue,
                                                     NrtGeoVector3F point);
    void Nrt_GeoVector3F_RotateToAngleAroundPointRad(NrtGeoVector3F* vector,
                                                     float angleRotationValue,
                                                     NrtGeoVector3F point);
    NrtBool Nrt_GeoVector3F_EpsilonEquals(NrtGeoVector3F vector, NrtGeoVector3F other, NrtGeoVector3F epsilonValue);
    NrtGeoVector3F Nrt_GeoVector3F_GetNormalised(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_GetLength(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_GetMagnitude(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_GetSquaredLength(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_GetSquaredMagnitude(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_Dot(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_Cross(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    float Nrt_GeoVector3F_Distance(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    float Nrt_GeoVector3F_SquaredDistance(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_Equal(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_NotEqual(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_LessThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_LessThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_GreaterThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_GreaterThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_AddVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_SubtractVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_MultiplyVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_DivideVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_AddFloat(NrtGeoVector3F lhs, float rhs);
    NrtGeoVector3F Nrt_GeoVector3F_SubtractFloat(NrtGeoVector3F lhs, float rhs);
    NrtGeoVector3F Nrt_GeoVector3F_MultiplyFloat(NrtGeoVector3F lhs, float rhs);
    NrtGeoVector3F Nrt_GeoVector3F_DivideFloat(NrtGeoVector3F lhs, float rhs);
    void Nrt_GeoVector3F_AddAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_SubtractAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_MultiplyAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_DivideAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_AddAssignFloat(NrtGeoVector3F* lhs, float rhs);
    void Nrt_GeoVector3F_SubtractAssignFloat(NrtGeoVector3F* lhs, float rhs);
    void Nrt_GeoVector3F_MultiplyAssignFloat(NrtGeoVector3F* lhs, float rhs);
    void Nrt_GeoVector3F_DivideAssignFloat(NrtGeoVector3F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
