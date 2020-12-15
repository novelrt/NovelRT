// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
#define NOVELRT_INTEROP_MATHS_GEOBOUNDS_H

#include "NrtGeoVector2F.h"
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    NrtGeoVector2F position;
    NrtGeoVector2F size;
    float rotation;
  } NrtGeoBounds;

  NrtGeoBounds Nrt_GeoBounds_zero();
  NrtGeoVector2F Nrt_GeoBounds_getCornerInLocalSpace(NrtGeoBounds bounds, int32_t index);
  NrtGeoVector2F Nrt_GeoBounds_getCornerInWorldSpace(NrtGeoBounds bounds, int32_t index);
  NrtBool Nrt_GeoBounds_pointIsWithinBounds(NrtGeoBounds bounds, NrtGeoVector2F point);
  NrtGeoVector2F Nrt_GeoBounds_getExtents(NrtGeoBounds bounds);
  NrtResult Nrt_GeoBounds_intersectsWith(NrtGeoBounds first, NrtGeoBounds other, NrtBool* outputResult); //TODO: This should NOT be an NrtResult wtf
  NrtBool Nrt_GeoBounds_equal(NrtGeoBounds lhs, NrtGeoBounds rhs);
  NrtBool Nrt_GeoBounds_notEqual(NrtGeoBounds lhs, NrtGeoBounds rhs);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
