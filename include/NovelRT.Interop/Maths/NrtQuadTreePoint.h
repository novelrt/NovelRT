// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H
#define NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H

#include "NrtGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct QuadtreePoint* NrtQuadTreePoint;

  NrtQuadTreePoint Nrt_QuadTreePoint_create(NrtGeoVector2F position);
  NrtQuadTreePoint Nrt_QuadTreePoint_createFromFloat(float x, float y);
  NrtGeoVector2F Nrt_QuadTreePoint_getPosition(const NrtQuadTreePoint point);
  NrtResult Nrt_QuadTreePoint_delete(NrtQuadTreePoint point);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_QUADTREEPOINT_H
