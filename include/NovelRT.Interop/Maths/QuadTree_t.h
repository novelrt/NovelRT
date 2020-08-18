// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Maths/NovelRTQuadTreePoint.h"
#include "NovelRT.Interop/Maths/NovelRTGeoBounds.h"
#include <cmath>
#include <stddef.h>

#ifndef NOVELRT_MATHS_QUADTREE_C_H
#define NOVELRT_MATHS_QUADTREE_C_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct QuadTreeHandle* NovelRTQuadTree;
  typedef struct StdVector_QuadTreePoint* NovelRTPointVector;


  NovelRTQuadTree NovelRT_QuadTree_create(NovelRTGeoBounds bounds);
  NovelRTQuadTree NovelRT_QuadTree_getParent(NovelRTQuadTree tree);
  NovelRTGeoBounds NovelRT_QuadTree_getBounds(NovelRTQuadTree tree);
  NovelRTQuadTreePoint NovelRT_QuadTree_getPoint(NovelRTQuadTree tree, size_t index);
  size_t NovelRT_QuadTree_getPointCount(NovelRTQuadTree tree);
  NovelRTQuadTree NovelRT_QuadTree_getTopLeft(NovelRTQuadTree tree);
  NovelRTQuadTree NovelRT_QuadTree_getTopRight(NovelRTQuadTree tree);
  NovelRTQuadTree NovelRT_QuadTree_getBottomLeft(NovelRTQuadTree tree);
  NovelRTQuadTree NovelRT_QuadTree_getBottomRight(NovelRTQuadTree tree);
  bool NovelRT_QuadTree_tryInsert(NovelRTQuadTree tree, NovelRTQuadTreePoint point);
  bool NovelRT_QuadTree_tryRemove(NovelRTQuadTree tree, NovelRTQuadTreePoint point);
  NovelRTPointVector NovelRT_QuadTree_getIntersectingPoints(NovelRTQuadTree tree, NovelRTGeoBounds bounds);
  void NovelRT_PointVector_delete(NovelRTPointVector vector);
  size_t NovelRT_PointVector_getSize(NovelRTPointVector vector);
  NovelRTQuadTreePoint NovelRT_PointVector_getPointFromIndex(NovelRTPointVector vector, size_t index);
  void NovelRT_QuadTree_delete(NovelRTQuadTree tree);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
