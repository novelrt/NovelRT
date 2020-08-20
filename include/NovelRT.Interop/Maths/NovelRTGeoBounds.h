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
    float rotation;
    NovelRTGeoVector2F size;
  } NovelRTGeoBounds;

  NovelRTGeoBounds NovelRT_GeoBounds_zero();
  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInLocalSpace(const NovelRTGeoBounds bounds, int index);
  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInWorldSpace(const NovelRTGeoBounds bounds, int index);
  NovelRTBool NovelRT_GeoBounds_pointIsWithinBounds(const NovelRTGeoBounds bounds, const NovelRTGeoVector2F point);
  NovelRTGeoVector2F NovelRT_GeoBounds_getExtents(const NovelRTGeoBounds bounds);
  NovelRTBool NovelRT_GeoBounds_intersectsWith(const NovelRTGeoBounds first, const NovelRTGeoBounds other);

  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
