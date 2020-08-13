// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"
#include "NovelRT.Interop/Maths/GeoBounds_t.h"


#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  GeoBounds_t GeoBounds_create(const NovelRTGeoVector2F& position, const NovelRTGeoVector2F& size, float rotation) {
    return GeoBounds_t{ position, rotation, size };
  }

  NovelRTGeoVector2F GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index) {
    const Maths::GeoBounds& cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2<float> corner = cBounds.getCornerInLocalSpace(index);
    return reinterpret_cast<NovelRTGeoVector2F&>(corner);
  }

  NovelRTGeoVector2F GeoBounds_getCornerInWorldSpace(const GeoBounds_t& bounds, int index) {
    const Maths::GeoBounds& cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2<float> corner = cBounds.getCornerInWorldSpace(index);
    return reinterpret_cast<NovelRTGeoVector2F&>(corner);
  }

  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const NovelRTGeoVector2F& point) {
    const Maths::GeoBounds& cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    const Maths::GeoVector2<float>& cPoint = reinterpret_cast<const Maths::GeoVector2<float>&>(point);
    return cBounds.pointIsWithinBounds(cPoint);
  }

  NovelRTGeoVector2F GeoBounds_getExtents(const GeoBounds_t& bounds) {
    const Maths::GeoBounds cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2<float> extents = cBounds.getExtents(); 
    return reinterpret_cast<NovelRTGeoVector2F&>(extents);
  }

  bool GeoBounds_intersectsWith(const GeoBounds_t& first, const GeoBounds_t& other) {
    const Maths::GeoBounds& cFirst = reinterpret_cast<const Maths::GeoBounds&>(first);
    const Maths::GeoBounds& cOther = reinterpret_cast<const Maths::GeoBounds&>(other);
    return cFirst.intersectsWith(cOther);
  }
}

