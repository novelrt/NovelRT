// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H

#include "NrtGeoVector3F.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtGeoVector4F Nrt_GeoVector4F_CreateFromGeoVector2F(NrtGeoVector2F vector);
    NrtGeoVector4F Nrt_GeoVector4F_CreateFromGeoVector3F(NrtGeoVector3F vector);
    NrtBool Nrt_GeoVector4F_IsNaN(NrtGeoVector4F vector);
    NrtGeoVector4F Nrt_GeoVector4F_Uniform(float value);
    NrtGeoVector4F Nrt_GeoVector4F_Zero();
    NrtGeoVector4F Nrt_GeoVector4F_One();
    void Nrt_GeoVector4F_RotateToAngleAroundPointDeg(NrtGeoVector4F* const vector,
                                                     float angleRotationValue,
                                                     NrtGeoVector3F point);
    void Nrt_GeoVector4F_RotateToAngleAroundPointRad(NrtGeoVector4F* const vector,
                                                     float angleRotationValue,
                                                     NrtGeoVector3F point);
    NrtBool Nrt_GeoVector4F_EpsilonEquals(NrtGeoVector4F vector, NrtGeoVector4F other, NrtGeoVector4F epsilonValue);
    NrtGeoVector4F Nrt_GeoVector4F_GetNormalised(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_GetLength(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_GetMagnitude(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_GetSquaredLength(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_GetSquaredMagnitude(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_Dot(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    float Nrt_GeoVector4F_Distance(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    float Nrt_GeoVector4F_SquaredDistance(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_Equal(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_NotEqual(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_LessThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_LessThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_GreaterThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_GreaterThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_AddVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_SubtractVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_MultiplyVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_DivideVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_AddFloat(NrtGeoVector4F lhs, float rhs);
    NrtGeoVector4F Nrt_GeoVector4F_SubtractFloat(NrtGeoVector4F lhs, float rhs);
    NrtGeoVector4F Nrt_GeoVector4F_MultiplyFloat(NrtGeoVector4F lhs, float rhs);
    NrtGeoVector4F Nrt_GeoVector4F_DivideFloat(NrtGeoVector4F lhs, float rhs);
    void Nrt_GeoVector4F_AddAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_SubtractAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_MultiplyAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_DivideAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_AddAssignFloat(NrtGeoVector4F* lhs, float rhs);
    void Nrt_GeoVector4F_SubtractAssignFloat(NrtGeoVector4F* lhs, float rhs);
    void Nrt_GeoVector4F_MultiplyAssignFloat(NrtGeoVector4F* lhs, float rhs);
    void Nrt_GeoVector4F_DivideAssignFloat(NrtGeoVector4F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
