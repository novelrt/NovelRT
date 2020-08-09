// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"

#ifndef NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
#define NOVELRT_INTEROP_MATHS_GEOBOUNDS_H

#ifdef __cplusplus
extern "C" {
#endif
  struct GeoBounds_t
  {
    GeoVector2F_t _position;
    float _rotation;
    GeoVector2F_t _size;
  };

  GeoBounds_t GeoBounds_create(const GeoVector2F_t& position, const GeoVector2F_t& size, float rotation);
  GeoVector2F_t GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index);
  GeoVector2F_t GeoBounds_getCornerInWorldSpace(GeoBounds_t& bounds, int index);
  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const GeoVector2F_t& point);
  GeoVector2F_t GeoBounds_getExtents(GeoBounds_t& bounds);
  bool GeoBounds_intersectsWith(const GeoBounds_t& first, const GeoBounds_t& other);

  
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOBOUNDS_H
