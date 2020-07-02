// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include "NovelRTInterop/Maths/QuadTreePoint_t.h"
#include "NovelRTInterop/Maths/GeoBounds_t.h"

#ifndef NOVELRT_MATHS_QUADTREE_C_H
#define NOVELRT_MATHS_QUADTREE_C_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct QuadTree_t* Quadtree;
  typedef struct StdVector_QuadTreePoint* PointVector;

  Quadtree QuadTree_create(GeoBounds_t& bounds);
  const Quadtree QuadTree_getParent(Quadtree tree);
  const GeoBounds_t QuadTree_getBounds(Quadtree tree);
  const QuadTreePoint_t QuadTree_getPoint(Quadtree tree, size_t index);
  size_t QuadTree_getPointCount(Quadtree tree);
  const Quadtree QuadTree_getTopLeft(Quadtree tree);
  const Quadtree QuadTree_getTopRight(Quadtree tree);
  const Quadtree QuadTree_getBottomLeft(Quadtree tree);
  const Quadtree QuadTree_getBottomRight(Quadtree tree);
  bool QuadTree_tryInsert(Quadtree tree, QuadTreePoint_t& point);
  bool QuadTree_tryRemove(Quadtree tree, QuadTreePoint_t& point);
  PointVector QuadTree_getIntersectingPoints(Quadtree tree, const GeoBounds_t& bounds);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
