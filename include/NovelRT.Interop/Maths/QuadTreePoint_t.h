// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"

#ifndef NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H
#define NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct QuadtreePoint* QuadTreePoint_t;
  
  QuadTreePoint_t QuadTreePoint_create(NovelRTGeoVector2F& position);
  QuadTreePoint_t QuadTreePoint_createFromFloat(float x, float y);
  NovelRTGeoVector2F QuadTreePoint_getPosition(QuadTreePoint_t point);
  void QuadTreePoint_delete(QuadTreePoint_t point);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H
