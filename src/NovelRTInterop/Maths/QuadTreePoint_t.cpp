// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTreePoint_t.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTreePoint_t* QuadTreePoint_create(GeoVector2F_t* position) {
    static Maths::QuadTreePoint* point = new Maths::QuadTreePoint(*reinterpret_cast<Maths::GeoVector2<float>*>(position));
    return reinterpret_cast<QuadTreePoint_t*>(point);
  }

  QuadTreePoint_t* QuadTreePoint_createFromFloat(float x, float y) {
    Maths::QuadTreePoint* point = new Maths::QuadTreePoint(x, y);
    return reinterpret_cast<QuadTreePoint_t*>(point);
  }

  const GeoVector2F_t* QuadTreePoint_getPosition(QuadTreePoint_t* point) {
    static Maths::GeoVector2<float> position = reinterpret_cast<Maths::QuadTreePoint*>(point)->getPosition();
    return reinterpret_cast<GeoVector2F_t*>(&position);
  }

#ifdef __cplusplus
}
#endif
