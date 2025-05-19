// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_QUADTREE_H
#define NOVELRT_INTEROP_MATHS_QUADTREE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtQuadTreeHandle Nrt_QuadTree_Create(NrtGeoBounds bounds);
    NrtResult Nrt_QuadTree_GetParent(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputParentTree);
    NrtGeoBounds Nrt_QuadTree_GetBounds(const NrtQuadTreeHandle tree);
    NrtResult Nrt_QuadTree_GetPoint(const NrtQuadTreeHandle tree, size_t index, NrtQuadTreePointHandle* outputPoint);
    size_t Nrt_QuadTree_GetPointCount(const NrtQuadTreeHandle tree);
    NrtResult Nrt_QuadTree_GetTopLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtResult Nrt_QuadTree_GetTopRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtResult Nrt_QuadTree_GetBottomLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtResult Nrt_QuadTree_GetBottomRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree);
    NrtBool Nrt_QuadTree_TryInsert(NrtQuadTreeHandle tree, NrtQuadTreePointHandle point);
    NrtBool Nrt_QuadTree_TryRemove(const NrtQuadTreeHandle tree, NrtQuadTreePointHandle point);
    NrtResult Nrt_QuadTree_GetIntersectingPoints(const NrtQuadTreeHandle tree,
                                                 NrtGeoBounds bounds,
                                                 NrtPointVectorHandle* outputResultVector);
    NrtResult Nrt_PointVector_Destroy(NrtPointVectorHandle vector);
    size_t Nrt_PointVector_GetSize(const NrtPointVectorHandle vector);
    NrtResult Nrt_PointVector_GetPointFromIndex(const NrtPointVectorHandle vector,
                                                size_t index,
                                                NrtQuadTreePointHandle* outputPoint);
    NrtResult Nrt_QuadTree_Destroy(NrtQuadTreeHandle tree);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_QUADTREE_H
