// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_QUADTREE_C_H
#define NOVELRT_MATHS_QUADTREE_C_H

#include "NrtGeoBounds.h"
#include "NrtQuadTreePoint.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct QuadTreeHandle* NrtQuadTree;
    typedef struct StdVector_QuadTreePoint* NrtPointVector;

    NrtQuadTree Nrt_QuadTree_create(NrtGeoBounds bounds);
    NrtResult Nrt_QuadTree_getParent(const NrtQuadTree tree, NrtQuadTree* outputParentTree);
    NrtGeoBounds Nrt_QuadTree_getBounds(const NrtQuadTree tree);
    NrtResult Nrt_QuadTree_getPoint(const NrtQuadTree tree, size_t index, NrtQuadTreePoint* outputPoint);
    size_t Nrt_QuadTree_getPointCount(const NrtQuadTree tree);
    NrtResult Nrt_QuadTree_getTopLeft(const NrtQuadTree tree, NrtQuadTree* outputCornerTree);
    NrtResult Nrt_QuadTree_getTopRight(const NrtQuadTree tree, NrtQuadTree* outputCornerTree);
    NrtResult Nrt_QuadTree_getBottomLeft(const NrtQuadTree tree, NrtQuadTree* outputCornerTree);
    NrtResult Nrt_QuadTree_getBottomRight(const NrtQuadTree tree, NrtQuadTree* outputCornerTree);
    NrtBool Nrt_QuadTree_tryInsert(NrtQuadTree tree, NrtQuadTreePoint point);
    NrtBool Nrt_QuadTree_tryRemove(const NrtQuadTree tree, NrtQuadTreePoint point);
    NrtResult Nrt_QuadTree_getIntersectingPoints(const NrtQuadTree tree,
                                                 NrtGeoBounds bounds,
                                                 NrtPointVector* outputResultVector);
    NrtResult Nrt_PointVector_delete(NrtPointVector vector);
    size_t Nrt_PointVector_getSize(const NrtPointVector vector);
    NrtResult Nrt_PointVector_getPointFromIndex(const NrtPointVector vector,
                                                size_t index,
                                                NrtQuadTreePoint* outputPoint);
    NrtResult Nrt_QuadTree_delete(NrtQuadTree tree);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_MATHS_QUADTREE_C_H
