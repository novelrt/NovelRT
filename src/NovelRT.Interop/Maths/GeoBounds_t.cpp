// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"
#include "NovelRT.Interop/Maths/GeoBounds_t.h"


#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  GeoBounds_t GeoBounds_create(const GeoVector2F_t& position, const GeoVector2F_t& size, float rotation) {
    return GeoBounds_t{ position, rotation, size };
  }

  GeoVector2F_t GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index) {
    const Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2<float>* corner = new Maths::GeoVector2<float>();
    *corner = cBounds.getCornerInLocalSpace(index);
    return reinterpret_cast<GeoVector2F_t&>(corner);
  }

  GeoVector2F_t GeoBounds_getCornerInWorldSpace(GeoBounds_t& bounds, int index) {
    const Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2<float>* corner = new Maths::GeoVector2<float>();
    *corner = cBounds.getCornerInWorldSpace(index);
    return reinterpret_cast<GeoVector2F_t&>(corner);
  }

  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const GeoVector2F_t& point) {
    const Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    const Maths::GeoVector2<float> cPoint = *reinterpret_cast<const Maths::GeoVector2<float>*>(&point);
    return cBounds.pointIsWithinBounds(cPoint);
  }

  GeoVector2F_t GeoBounds_getExtents(GeoBounds_t& bounds) {
    Maths::GeoBounds cBounds = *reinterpret_cast<Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2<float>* extents = new Maths::GeoVector2<float>();
    *extents = cBounds.getExtents(); 
    return reinterpret_cast<GeoVector2F_t&>(*extents);
  }

  bool GeoBounds_intersectsWith(const GeoBounds_t& first, const GeoBounds_t& other) {
    const Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&first);
    const Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&other);
    return cFirst.intersectsWith(cOther);
  }
}

