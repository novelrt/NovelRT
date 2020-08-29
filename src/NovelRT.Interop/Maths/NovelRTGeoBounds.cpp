// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/Maths/NovelRTGeoBounds.h"


#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  NovelRTGeoBounds NovelRT_GeoBounds_zero() {
    return NovelRTGeoBounds{ NovelRT_GeoVector2F_zero(), 0.0f, NovelRT_GeoVector2F_zero() };
  }

  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInLocalSpace(const NovelRTGeoBounds bounds, int index) {
    const Maths::GeoBounds& cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2F corner = cBounds.getCornerInLocalSpace(index);
    return reinterpret_cast<NovelRTGeoVector2F&>(corner);
  }

  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInWorldSpace(const NovelRTGeoBounds bounds, int index) {
    const Maths::GeoBounds& cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2F corner = cBounds.getCornerInWorldSpace(index);
    return reinterpret_cast<NovelRTGeoVector2F&>(corner);
  }

  NovelRTBool NovelRT_GeoBounds_pointIsWithinBounds(const NovelRTGeoBounds bounds, NovelRTGeoVector2F point) {
    const Maths::GeoBounds& cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2F cPoint = *reinterpret_cast<Maths::GeoVector2F*>(&point);
    if (cBounds.pointIsWithinBounds(cPoint)) {
      return NOVELRT_TRUE;
    }
    return NOVELRT_FALSE;
  }

  NovelRTGeoVector2F NovelRT_GeoBounds_getExtents(const NovelRTGeoBounds bounds) {
    const Maths::GeoBounds cBounds = reinterpret_cast<const Maths::GeoBounds&>(bounds);
    Maths::GeoVector2F extents = cBounds.getExtents(); 
    return reinterpret_cast<NovelRTGeoVector2F&>(extents);
  }

  NovelRTBool NovelRT_GeoBounds_intersectsWith(const NovelRTGeoBounds first, const NovelRTGeoBounds other) {
    const Maths::GeoBounds& cFirst = reinterpret_cast<const Maths::GeoBounds&>(first);
    const Maths::GeoBounds& cOther = reinterpret_cast<const Maths::GeoBounds&>(other);
    if (cFirst.intersectsWith(cOther)) {
      return NOVELRT_TRUE;
    }
    return NOVELRT_FALSE;
  }
}

