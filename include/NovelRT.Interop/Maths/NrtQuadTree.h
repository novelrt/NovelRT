// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_QUADTREE_H
#define NOVELRT_INTEROP_MATHS_QUADTREE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtQuadTreeHandle Nrt_QuadTree_create(NrtGeoBounds bounds);
    NrtResult Nrt_QuadTree_getParent(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputParentTree);
    NrtGeoBounds Nrt_QuadTree_getBounds(const NrtQuadTreeHandle tree);
    NrtResult Nrt_QuadTree_getPoint(const NrtQuadTreeHandle tree, size_t index, NrtQuadTreePointHandle* outputPoint);
    size_t Nrt_QuadTree_getPointCount(const NrtQuadTreeHandle tree);
    NrtResult Nrt_QuadTree_getTopLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtResult Nrt_QuadTree_getTopRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtResult Nrt_QuadTree_getBottomLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtResult Nrt_QuadTree_getBottomRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtBool Nrt_QuadTree_tryInsert(NrtQuadTreeHandle tree, NrtQuadTreePointHandle point);
    NrtBool Nrt_QuadTree_tryRemove(const NrtQuadTreeHandle tree, NrtQuadTreePointHandle point);
    NrtResult Nrt_QuadTree_getIntersectingPoints(const NrtQuadTreeHandle tree,
                                                 NrtGeoBounds bounds,
                                                 NrtPointVectorHandle* outputResultVector);
    NrtResult Nrt_PointVector_Destroy(NrtPointVectorHandle vector);
    size_t Nrt_PointVector_getSize(const NrtPointVectorHandle vector);
    NrtResult Nrt_PointVector_getPointFromIndex(const NrtPointVectorHandle vector,
                                                size_t index,
                                                NrtQuadTreePointHandle* outputPoint);
    NrtResult Nrt_QuadTree_Destroy(NrtQuadTreeHandle tree);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_QUADTREE_H
