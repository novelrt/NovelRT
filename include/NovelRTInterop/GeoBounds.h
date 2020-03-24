// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "GeoVector2F.h"
#include "NovelRT.h"


#ifndef NOVELRT_MATHS_GEOBOUNDS_C_H
#define NOVELRT_MATHS_GEOBOUNDS_C_H

#ifdef __cplusplus
extern "C" {
#endif

 struct GeoBounds {
   GeoVector2F_t _position;
   float _rotation;
   GeoVector2F_t _size;
 };

typedef struct GeoBounds GeoBounds_t;

GeoBounds_t GeoBounds_create(const GeoVector2F_t& position, const GeoVector2F_t& size, float rotation);
GeoVector2F_t GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index);
GeoVector2F_t GeoBounds_getCornerInWorldSpace(GeoBounds_t& bounds, int index);
bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const GeoVector2F_t& point);
const GeoVector2F& GeoBounds_position(const GeoBounds_t& bounds);
const GeoVector2F& GeoBounds_size(const GeoBounds_t& bounds);
const float& GeoBounds_rotation(const GeoBounds_t& bounds);
GeoVector2F_t GeoBounds_getExtents(GeoBounds_t& bounds);
bool GeoBounds_intersectsWith(const GeoBounds_t& firstBounds, const GeoBounds_t& otherBounds);

inline bool GeoBounds_equal(const GeoBounds_t& first, const GeoBounds_t& other) {
  return GeoVector2F_equal(first._position, other._position)
    && GeoVector2F_equal(first._size, other._size)
    && first._rotation == other._rotation;
}

inline bool GeoBounds_notEqual(const GeoBounds_t& first, const GeoBounds_t& other) {
  return GeoVector2F_notEqual(first._position, other._position)
    || GeoVector2F_notEqual(first._size, other._size)
    || first._rotation != other._rotation;
}

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOBOUNDS_C_H
