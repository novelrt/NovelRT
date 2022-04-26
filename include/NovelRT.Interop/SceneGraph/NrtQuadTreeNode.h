// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QUADTREENODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_QUADTREENODE_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_QuadTreeNode_create(NrtQuadTreeScenePointArrayHandle points, NrtQuadTreeNodeHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_getTopLeft(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_getTopRight(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_getBottomLeft(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_getBottomRight(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);

    NrtResult Nrt_QuadTreeScenePointArray_create(NrtQuadTreeScenePointHandle pointOne,
                                                 NrtQuadTreeScenePointHandle pointTwo,
                                                 NrtQuadTreeScenePointHandle pointThree,
                                                 NrtQuadTreeScenePointHandle pointFour,
                                                 NrtQuadTreeScenePointArrayHandle* outputArray);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_QUADTREENODE_H
