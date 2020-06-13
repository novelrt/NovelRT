// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/GeoVector2F_t.h"

#ifndef NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H
#define NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef void QuadTreePoint_t;

  QuadTreePoint_t* QuadTreePoint_create(GeoVector2F_t* position);
  QuadTreePoint_t* QuadTreePoint_createFromFloat(float x, float y);
  const GeoVector2F_t* QuadTreePoint_getPosition(QuadTreePoint_t* point);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H
