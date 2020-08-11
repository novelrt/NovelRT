// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Maths/QuadTreePoint_t.h"
#include "NovelRT.Interop/Maths/GeoBounds_t.h"
#include <cmath>
#include <stddef.h>

#ifndef NOVELRT_MATHS_QUADTREE_C_H
#define NOVELRT_MATHS_QUADTREE_C_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct QuadTreeHandle* QuadTree_t;
  typedef struct StdVector_QuadTreePoint* PointVector;

  QuadTree_t QuadTree_create(const GeoBounds_t& bounds);
  QuadTree_t QuadTree_getParent(QuadTree_t tree);
  GeoBounds_t QuadTree_getBounds(QuadTree_t tree);
  QuadTreePoint_t QuadTree_getPoint(QuadTree_t tree, size_t index);
  size_t QuadTree_getPointCount(QuadTree_t tree);
  QuadTree_t QuadTree_getTopLeft(QuadTree_t tree);
  QuadTree_t QuadTree_getTopRight(QuadTree_t tree);
  QuadTree_t QuadTree_getBottomLeft(QuadTree_t tree);
  QuadTree_t QuadTree_getBottomRight(QuadTree_t tree);
  bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t point);
  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t point);
  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds);
  void PointVector_delete(PointVector vector);
  size_t PointVector_getSize(PointVector vector);
  QuadTreePoint_t PointVector_getPointFromIndex(PointVector vector, size_t index);
  void QuadTree_delete(QuadTree_t tree);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
