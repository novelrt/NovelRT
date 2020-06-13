// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include "NovelRTInterop/Maths/QuadTreePoint_t.h"
#include "NovelRTInterop/Maths/GeoBounds_t.h"

#ifndef NOVELRT_MATHS_QUADTREE_C_H
#define NOVELRT_MATHS_QUADTREE_C_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef void QuadTree_t;

  QuadTree_t* QuadTree_create(GeoBounds_t* bounds);
  const QuadTree_t* QuadTree_getParent(QuadTree_t* tree);
  const GeoBounds_t* QuadTree_getBounds(QuadTree_t* tree);
  const QuadTreePoint_t* QuadTree_getPoint(QuadTree_t* tree, size_t index);
  size_t QuadTree_getPointCount(QuadTree_t* tree);
  const QuadTree_t* QuadTree_getTopLeft(QuadTree_t* tree);
  const QuadTree_t* QuadTree_getTopRight(QuadTree_t* tree);
  const QuadTree_t* QuadTree_getBottomLeft(QuadTree_t* tree);
  const QuadTree_t* QuadTree_getBottomRight(QuadTree_t* tree);
  bool QuadTree_tryInsert(QuadTree_t* tree, QuadTreePoint_t* point);

  //Template with template args... yikes
  //bool tryInsert(const GeoBounds& bounds, TArgs... args)
  //bool tryRemove(std::shared_ptr<QuadTreePoint> point)

  //Template
  //const std::shared_ptr<TQuadTreePoint>& getPoint(size_t index);

  //Needs a vector
  //void getIntersectingPoints(const GeoBounds& bounds, std::vector<std::shared_ptr<QuadTreePoint>>& intersectingPoints)
  //std::vector<std::shared_ptr<QuadTreePoint>> getIntersectingPoints(const GeoBounds& bounds)
#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
