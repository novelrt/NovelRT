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
  NovelRTResult NovelRT_QuadTree_getParent(const NovelRTQuadTree const tree, NovelRTQuadTree* outputParentTree, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getBounds(NovelRTQuadTree tree, NovelRTGeoBounds* outputGeoBounds, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getPoint(const NovelRTQuadTree const tree, size_t index, NovelRTQuadTreePoint* outputPoint, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getPointCount(const NovelRTQuadTree const tree, size_t* outputSize, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getTopLeft(const NovelRTQuadTree const tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getTopRight(const NovelRTQuadTree const tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getBottomLeft(const NovelRTQuadTree const tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getBottomRight(const NovelRTQuadTree const tree, NovelRTQuadTree* outputCornerTree, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_tryInsert(NovelRTQuadTree const tree, NovelRTQuadTreePoint point, NovelRTBool* outputResult, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_tryRemove(NovelRTQuadTree const tree, NovelRTQuadTreePoint point, NovelRTBool* outputResult, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_getIntersectingPoints(const NovelRTQuadTree const tree, NovelRTGeoBounds bounds, NovelRTPointVector* outputResultVector, const char** errorMessage);
  NovelRTResult NovelRT_PointVector_delete(NovelRTPointVector vector, const char** errorMessage);
  NovelRTResult NovelRT_PointVector_getSize(const NovelRTPointVector const vector, size_t* outputSize, const char** errorMessage);
  NovelRTResult NovelRT_PointVector_getPointFromIndex(const NovelRTPointVector const vector, size_t index, NovelRTQuadTreePoint* outputPoint, const char** errorMessage);
  NovelRTResult NovelRT_QuadTree_delete(NovelRTQuadTree tree, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_QUADTREE_C_H
