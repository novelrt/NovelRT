// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H

#include "NrtGeoVector2F.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtGeoVector3F Nrt_GeoVector3F_createFromGeoVector2F(NrtGeoVector2F vector);
    NrtBool Nrt_GeoVector3F_isNaN(NrtGeoVector3F vector);
    NrtGeoVector3F Nrt_GeoVector3F_uniform(float value);
    NrtGeoVector3F Nrt_GeoVector3F_zero();
    NrtGeoVector3F Nrt_GeoVector3F_one();
    void Nrt_GeoVector3F_rotateToAngleAroundPoint(NrtGeoVector3F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector3F point);
    NrtBool Nrt_GeoVector3F_epsilonEquals(NrtGeoVector3F vector, NrtGeoVector3F other, NrtGeoVector3F epsilonValue);
    NrtGeoVector3F Nrt_GeoVector3F_getNormalised(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_getLength(NrtGeoVector3F vector);
    float Nrt_GeoVector3F_getMagnitude(NrtGeoVector3F vector);
    NrtBool Nrt_GeoVector3F_equal(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_notEqual(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_lessThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_lessThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_greaterThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtBool Nrt_GeoVector3F_greaterThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_addVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_subtractVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_multiplyVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_divideVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);
    NrtGeoVector3F Nrt_GeoVector3F_addFloat(NrtGeoVector3F lhs, float rhs);
    NrtGeoVector3F Nrt_GeoVector3F_subtractFloat(NrtGeoVector3F lhs, float rhs);
    NrtGeoVector3F Nrt_GeoVector3F_multiplyFloat(NrtGeoVector3F lhs, float rhs);
    NrtGeoVector3F Nrt_GeoVector3F_divideFloat(NrtGeoVector3F lhs, float rhs);
    void Nrt_GeoVector3F_addAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_subtractAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_multiplyAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_divideAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);
    void Nrt_GeoVector3F_addAssignFloat(NrtGeoVector3F* lhs, float rhs);
    void Nrt_GeoVector3F_subtractAssignFloat(NrtGeoVector3F* lhs, float rhs);
    void Nrt_GeoVector3F_multiplyAssignFloat(NrtGeoVector3F* lhs, float rhs);
    void Nrt_GeoVector3F_divideAssignFloat(NrtGeoVector3F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
