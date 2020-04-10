// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "GeoVector2F_t.h"
#include "NovelRT.h"


#ifndef NOVELRT_MATHS_GEOBOUNDS_T_H
#define NOVELRT_MATHS_GEOBOUNDS_T_H

#ifdef __cplusplus
extern "C" {
#endif

  using namespace NovelRT;

  typedef struct Maths::GeoBounds GeoBounds_t;

  GeoBounds_t GeoBounds_create(const GeoVector2F_t& position, const GeoVector2F_t& size, float rotation);
  GeoVector2F_t GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index);
  GeoVector2F_t GeoBounds_getCornerInWorldSpace(GeoBounds_t& bounds, int index);
  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const GeoVector2F_t& point);
  
  GeoVector2F_t GeoBounds_getExtents(GeoBounds_t& bounds);
  bool GeoBounds_intersectsWith(const GeoBounds_t& firstBounds, const GeoBounds_t& otherBounds);

  inline GeoVector2F_t GeoBounds_getPosition(const GeoBounds_t& bounds) {
    GeoVector2F_t result = bounds.position();
    return result;
  }

  inline GeoVector2F_t GeoBounds_getSize(const GeoBounds_t& bounds) {
    GeoVector2F_t result = bounds.size();
    return result;
  }

  inline float GeoBounds_getRotation(const GeoBounds_t& bounds) {
    float result = bounds.rotation();
    return result;
  }

  inline bool GeoBounds_equal(const GeoBounds_t& first, const GeoBounds_t& other) {
    return (first.position() == other.position()) && (first.size() == other.size()) && (first.rotation() == other.rotation());
  }

  inline bool GeoBounds_notEqual(const GeoBounds_t& first, const GeoBounds_t& other) {
    return (first.position() != other.position()) || (first.size() != other.size()) || (first.rotation() != other.rotation());
  }

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOBOUNDS_T_H
