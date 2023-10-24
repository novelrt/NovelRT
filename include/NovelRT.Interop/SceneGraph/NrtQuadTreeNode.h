// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QUADTREENODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_QUADTREENODE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_QuadTreeNode_Create(NrtQuadTreeScenePointArrayHandle points, NrtQuadTreeNodeHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_GetTopLeft(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_GetTopRight(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_GetBottomLeft(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);
    NrtResult Nrt_QuadTreeNode_GetBottomRight(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint);

    NrtResult Nrt_QuadTreeScenePointArray_Create(NrtQuadTreeScenePointHandle pointOne,
                                                 NrtQuadTreeScenePointHandle pointTwo,
                                                 NrtQuadTreeScenePointHandle pointThree,
                                                 NrtQuadTreeScenePointHandle pointFour,
                                                 NrtQuadTreeScenePointArrayHandle* outputArray);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_QUADTREENODE_H
