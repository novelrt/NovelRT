// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H
#define NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H

#include "NrtGeoVector4F.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct NrtGeoMatrix4x4F
    {
        NrtGeoVector4F x;
        NrtGeoVector4F y;
        NrtGeoVector4F z;
        NrtGeoVector4F w;
    };

    NrtBool Nrt_GeoMatrix4x4F_isNaN(NrtGeoMatrix4x4F matrix);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_getDefaultIdentity();
    NrtBool Nrt_GeoMatrix4x4F_equal(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtBool Nrt_GeoMatrix4x4F_notEqual(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_addMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_subtractMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_multiplyMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    void Nrt_GeoMatrix4x4F_addAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);
    void Nrt_GeoMatrix4x4F_subtractAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);
    void Nrt_GeoMatrix4x4F_multiplyAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F lhs, float rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F lhs, float rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_multiplyFloat(NrtGeoMatrix4x4F lhs, float rhs);
    void Nrt_GeoMatrix4x4F_addAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);
    void Nrt_GeoMatrix4x4F_subtractAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);
    void Nrt_GeoMatrix4x4F_multiplyAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H
