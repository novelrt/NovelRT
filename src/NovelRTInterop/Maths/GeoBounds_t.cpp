// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRTInterop/Maths/GeoVector2F_t.h"
#include "NovelRTInterop/Maths/GeoBounds_t.h"


#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  GeoBounds_t* GeoBounds_create(const GeoVector2F_t* position, const GeoVector2F_t* size, float rotation) {
    const Maths::GeoVector2<float>* cPosition = reinterpret_cast<const Maths::GeoVector2<float>*>(position);
    const Maths::GeoVector2<float>* cSize = reinterpret_cast<const Maths::GeoVector2<float>*>(size);
    Maths::GeoVector2<float> pos = { cPosition->getX(), cPosition->getY() };
    Maths::GeoVector2<float> sz = { cSize->getX(), cSize->getY() };
    static Maths::GeoBounds bounds = Maths::GeoBounds(pos, sz, rotation);
    return reinterpret_cast<GeoBounds_t*>(&bounds);
  }

  GeoVector2F_t* GeoBounds_getCornerInLocalSpace(const GeoBounds_t* bounds, int index) {
    const Maths::GeoBounds* cBounds = reinterpret_cast<const Maths::GeoBounds*>(bounds);
    static Maths::GeoVector2<float> corner = cBounds->getCornerInLocalSpace(index);
    return reinterpret_cast<GeoVector2F_t*>(&corner);
  }

  GeoVector2F_t* GeoBounds_getCornerInWorldSpace(GeoBounds_t* bounds, int index) {
    const Maths::GeoBounds* cBounds = reinterpret_cast<const Maths::GeoBounds*>(bounds);
    static Maths::GeoVector2<float> corner = cBounds->getCornerInWorldSpace(index);
    return reinterpret_cast<GeoVector2F_t*>(&corner);
  }

  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t* bounds, const GeoVector2F_t* point) {
    const Maths::GeoBounds* cBounds = reinterpret_cast<const Maths::GeoBounds*>(bounds);
    const Maths::GeoVector2<float>* cPoint = reinterpret_cast<const Maths::GeoVector2<float>*>(point);
    Maths::GeoVector2<float> pt = { cPoint->getX(), cPoint->getY() };
    return cBounds->pointIsWithinBounds(pt);
  }

  GeoVector2F_t* GeoBounds_getExtents(GeoBounds_t* bounds) {
    Maths::GeoBounds* cBounds = reinterpret_cast<Maths::GeoBounds*>(bounds);
    static Maths::GeoVector2<float> extents = cBounds->getExtents();
    return reinterpret_cast<GeoVector2F_t*>(&extents);
  }

  bool GeoBounds_intersectsWith(const GeoBounds_t* first, const GeoBounds_t* other) {
    const Maths::GeoBounds* cFirst = reinterpret_cast<const Maths::GeoBounds*>(first);
    const Maths::GeoBounds* cOther = reinterpret_cast<const Maths::GeoBounds*>(other);
    Maths::GeoBounds oth = Maths::GeoBounds(cOther->position(), cOther->size(), cOther->rotation());
    return cFirst->intersectsWith(oth);
  }
}

