// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H

#include "NrtGeoVector3F.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector2F(NrtGeoVector2F vector);
    NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector3F(NrtGeoVector3F vector);
    NrtBool Nrt_GeoVector4F_isNaN(NrtGeoVector4F vector);
    NrtGeoVector4F Nrt_GeoVector4F_uniform(float value);
    NrtGeoVector4F Nrt_GeoVector4F_zero();
    NrtGeoVector4F Nrt_GeoVector4F_one();
    void Nrt_GeoVector4F_RotateToAngleAroundPointDeg(NrtGeoVector4F* const vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector3F point);
    void Nrt_GeoVector4F_RotateToAngleAroundPointRad(NrtGeoVector4F* const vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector3F point);
    NrtBool Nrt_GeoVector4F_epsilonEquals(NrtGeoVector4F vector, NrtGeoVector4F other, NrtGeoVector4F epsilonValue);
    NrtGeoVector4F Nrt_GeoVector4F_getNormalised(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_getLength(NrtGeoVector4F vector);
    float Nrt_GeoVector4F_getMagnitude(NrtGeoVector4F vector);
    NrtBool Nrt_GeoVector4F_equal(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_notEqual(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_lessThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_lessThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_greaterThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtBool Nrt_GeoVector4F_greaterThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_addVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_subtractVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_multiplyVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_divideVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);
    NrtGeoVector4F Nrt_GeoVector4F_addFloat(NrtGeoVector4F lhs, float rhs);
    NrtGeoVector4F Nrt_GeoVector4F_subtractFloat(NrtGeoVector4F lhs, float rhs);
    NrtGeoVector4F Nrt_GeoVector4F_multiplyFloat(NrtGeoVector4F lhs, float rhs);
    NrtGeoVector4F Nrt_GeoVector4F_divideFloat(NrtGeoVector4F lhs, float rhs);
    void Nrt_GeoVector4F_addAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_subtractAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_multiplyAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_divideAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);
    void Nrt_GeoVector4F_addAssignFloat(NrtGeoVector4F* lhs, float rhs);
    void Nrt_GeoVector4F_subtractAssignFloat(NrtGeoVector4F* lhs, float rhs);
    void Nrt_GeoVector4F_multiplyAssignFloat(NrtGeoVector4F* lhs, float rhs);
    void Nrt_GeoVector4F_divideAssignFloat(NrtGeoVector4F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOVECTOR4F_H
