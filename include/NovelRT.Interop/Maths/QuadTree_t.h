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


  QuadTree_t NovelRT_QuadTree_create(const GeoBounds_t& bounds);
  QuadTree_t NovelRT_QuadTree_getParent(QuadTree_t tree);
  GeoBounds_t NovelRT_QuadTree_getBounds(QuadTree_t tree);
  QuadTreePoint_t NovelRT_QuadTree_getPoint(QuadTree_t tree, size_t index);
  size_t NovelRT_QuadTree_getPointCount(QuadTree_t tree);
  QuadTree_t NovelRT_QuadTree_getTopLeft(QuadTree_t tree);
  QuadTree_t NovelRT_QuadTree_getTopRight(QuadTree_t tree);
  QuadTree_t NovelRT_QuadTree_getBottomLeft(QuadTree_t tree);
  QuadTree_t NovelRT_QuadTree_getBottomRight(QuadTree_t tree);
  bool NovelRT_QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t point);
  bool NovelRT_QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t point);
  PointVector NovelRT_QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds);
  void NovelRT_PointVector_delete(PointVector vector);
  size_t NovelRT_PointVector_getSize(PointVector vector);
  QuadTreePoint_t NovelRT_PointVector_getPointFromIndex(PointVector vector, size_t index);
  void NovelRT_QuadTree_delete(QuadTree_t tree);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
