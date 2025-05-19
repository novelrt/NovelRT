// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H
#define NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H

#include "NrtGeoVector4F.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtBool Nrt_GeoMatrix4x4F_IsNaN(NrtGeoMatrix4x4F matrix);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_GetDefaultIdentity();
    NrtBool Nrt_GeoMatrix4x4F_Equal(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtBool Nrt_GeoMatrix4x4F_NotEqual(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_AddMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_SubtractMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_MultiplyMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);
    void Nrt_GeoMatrix4x4F_AddAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);
    void Nrt_GeoMatrix4x4F_SubtractAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);
    void Nrt_GeoMatrix4x4F_MultiplyAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_AddFloat(NrtGeoMatrix4x4F lhs, float rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_SubtractFloat(NrtGeoMatrix4x4F lhs, float rhs);
    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_MultiplyFloat(NrtGeoMatrix4x4F lhs, float rhs);
    void Nrt_GeoMatrix4x4F_AddAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);
    void Nrt_GeoMatrix4x4F_SubtractAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);
    void Nrt_GeoMatrix4x4F_MultiplyAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H
