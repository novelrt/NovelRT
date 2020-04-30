// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "GeoVector2F_t.h"
#include "NovelRT.h"

#ifndef NOVELRT_MATHS_QUADTREEPOINT_C_H
#define NOVELRT_MATHS_QUADTREEPOINT_C_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct NovelRT::Maths::QuadTreePoint QuadTreePoint_t;

  inline QuadTreePoint_t QuadTreePoint_create(GeoVector2F_t position) {
    return NovelRT::Maths::QuadTreePoint(position);
  }

  inline QuadTreePoint_t QuadTreePoint_createFromFloat(float x, float y) {
    return NovelRT::Maths::QuadTreePoint(NovelRT::Maths::GeoVector2<float>(x,y));
  }

  inline const GeoVector2F_t& QuadTreePoint_getPosition(QuadTreePoint_t point) {
    return point.getPosition();
  }

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREEPOINT_C_H
