// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"

#ifndef NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
#define NOVELRT_INTEROP_MATHS_GEOBOUNDS_H

#ifdef __cplusplus
extern "C" {
#endif
  struct GeoBounds_t
  {
    NovelRTGeoVector2F _position;
    float _rotation;
    NovelRTGeoVector2F _size;
  };

  GeoBounds_t GeoBounds_create(const NovelRTGeoVector2F& position, const NovelRTGeoVector2F& size, float rotation);
  NovelRTGeoVector2F GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index);
  NovelRTGeoVector2F GeoBounds_getCornerInWorldSpace(const GeoBounds_t& bounds, int index);
  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const NovelRTGeoVector2F& point);
  NovelRTGeoVector2F GeoBounds_getExtents(const GeoBounds_t& bounds);
  bool GeoBounds_intersectsWith(const GeoBounds_t& first, const GeoBounds_t& other);

  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
