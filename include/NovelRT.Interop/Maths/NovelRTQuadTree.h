// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRTQuadTreePoint.h"
#include "NovelRTGeoBounds.h"
#include <stddef.h>

#ifndef NOVELRT_MATHS_QUADTREE_C_H
#define NOVELRT_MATHS_QUADTREE_C_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct QuadTreeHandle* NovelRTQuadTree;
  typedef struct StdVector_QuadTreePoint* NovelRTPointVector;


  NovelRTQuadTree NovelRT_QuadTree_create(NovelRTGeoBounds bounds);
  int32_t NovelRT_QuadTree_getParent(const NovelRTQuadTree tree, NovelRTQuadTree* outputParentTree, const char** errorMessage);
  int32_t NovelRT_QuadTree_getBounds(const NovelRTQuadTree tree, NovelRTGeoBounds* outputGeoBounds, const char** errorMessage);
  int32_t NovelRT_QuadTree_getPoint(const NovelRTQuadTree tree, size_t index, NovelRTQuadTreePoint* outputPoint, const char** errorMessage);
  int32_t NovelRT_QuadTree_getPointCount(const NovelRTQuadTree tree, size_t* outputSize, const char** errorMessage);
  int32_t NovelRT_QuadTree_getTopLeft(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  int32_t NovelRT_QuadTree_getTopRight(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  int32_t NovelRT_QuadTree_getBottomLeft(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  int32_t NovelRT_QuadTree_getBottomRight(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  int32_t NovelRT_QuadTree_tryInsert(NovelRTQuadTree tree, NovelRTQuadTreePoint point, int32_t* outputResult, const char** errorMessage);
  int32_t NovelRT_QuadTree_tryRemove(const NovelRTQuadTree tree, NovelRTQuadTreePoint point, int32_t* outputResult, const char** errorMessage);
  int32_t NovelRT_QuadTree_getIntersectingPoints(const NovelRTQuadTree tree, NovelRTGeoBounds bounds, NovelRTPointVector* outputResultVector, const char** errorMessage);
  int32_t NovelRT_PointVector_delete(NovelRTPointVector vector, const char** errorMessage);
  int32_t NovelRT_PointVector_getSize(const NovelRTPointVector vector, size_t* outputSize, const char** errorMessage);
  int32_t NovelRT_PointVector_getPointFromIndex(const NovelRTPointVector vector, size_t index, NovelRTQuadTreePoint* outputPoint, const char** errorMessage);
  int32_t NovelRT_QuadTree_delete(NovelRTQuadTree tree, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
