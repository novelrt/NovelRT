// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"

#ifndef NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
#define NOVELRT_INTEROP_MATHS_GEOBOUNDS_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    NovelRTGeoVector2F position;
    NovelRTGeoVector2F size;
    float rotation;
  } NovelRTGeoBounds;

  NovelRTGeoBounds NovelRT_GeoBounds_zero();
  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInLocalSpace(NovelRTGeoBounds bounds, int index);
  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInWorldSpace(NovelRTGeoBounds bounds, int index);
  NovelRTBool NovelRT_GeoBounds_pointIsWithinBounds(NovelRTGeoBounds bounds, NovelRTGeoVector2F point);
  NovelRTGeoVector2F NovelRT_GeoBounds_getExtents(NovelRTGeoBounds bounds);
  NovelRTResult NovelRT_GeoBounds_intersectsWith(NovelRTGeoBounds first, NovelRTGeoBounds other, NovelRTBool* outputResult, const char** errorMessage);
  NovelRTBool NovelRT_GeoBounds_equal(NovelRTGeoBounds lhs, NovelRTGeoBounds rhs);
  NovelRTBool NovelRT_GeoBounds_notEqual(NovelRTGeoBounds lhs, NovelRTGeoBounds rhs);
  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
