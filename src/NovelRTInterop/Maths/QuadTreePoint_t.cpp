// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTreePoint_t.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTreePoint_t QuadTreePoint_create(GeoVector2F_t& position) {
    return QuadTreePoint_t{ position };
  }

  QuadTreePoint_t QuadTreePoint_createFromFloat(float x, float y) {
    return QuadTreePoint_t{ GeoVector2F_create(x, y) };
  }

  const GeoVector2F_t QuadTreePoint_getPosition(QuadTreePoint_t& point) {
    return point._position;
  }

#ifdef __cplusplus
}
#endif
