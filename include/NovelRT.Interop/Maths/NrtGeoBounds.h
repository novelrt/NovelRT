// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
#define NOVELRT_INTEROP_MATHS_GEOBOUNDS_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtGeoBounds Nrt_GeoBounds_Zero();
    NrtGeoVector2F Nrt_GeoBounds_GetCornerInLocalSpace(NrtGeoBounds bounds, int32_t index);
    NrtGeoVector2F Nrt_GeoBounds_GetCornerInWorldSpace(NrtGeoBounds bounds, int32_t index);
    NrtBool Nrt_GeoBounds_PointIsWithinBounds(NrtGeoBounds bounds, NrtGeoVector2F point);
    NrtGeoVector2F Nrt_GeoBounds_GetExtents(NrtGeoBounds bounds);
    NrtResult Nrt_GeoBounds_IntersectsWith(NrtGeoBounds first,
                                           NrtGeoBounds other,
                                           NrtBool* outputResult); // TODO: This should NOT be an NrtResult wtf
    NrtBool Nrt_GeoBounds_Equal(NrtGeoBounds lhs, NrtGeoBounds rhs);
    NrtBool Nrt_GeoBounds_NotEqual(NrtGeoBounds lhs, NrtGeoBounds rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
