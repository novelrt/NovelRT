// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSceneNodeHandle Nrt_SceneNode_Create();
    NrtResult Nrt_SceneNode_GetChildren(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet);
    NrtResult Nrt_SceneNode_GetParents(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet);
    NrtBool Nrt_SceneNode_Insert(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToInsert);
    NrtBool Nrt_SceneNode_Remove(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToRemove);
    NrtBool Nrt_SceneNode_IsAdjacent(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode);
    NrtResult Nrt_SceneNode_TraverseBreadthFirst(NrtSceneNodeHandle node,
                                                 void (*action)(NrtSceneNodeHandle, void*),
                                                 void* context);
    NrtResult Nrt_SceneNode_TraverseBreadthFirstWithIterator(NrtSceneNodeHandle node,
                                                             int32_t (*action)(NrtSceneNodeHandle, void*),
                                                             void* context,
                                                             NrtSceneNodeBreadthFirstIteratorHandle* outputIterator);
    NrtResult Nrt_SceneNode_TraverseDepthFirst(NrtSceneNodeHandle node,
                                               void (*action)(NrtSceneNodeHandle, void*),
                                               void* context);
    NrtResult Nrt_SceneNode_TraverseDepthFirstWithIterator(NrtSceneNodeHandle node,
                                                           int32_t (*action)(NrtSceneNodeHandle, void*),
                                                           void* context,
                                                           NrtSceneNodeDepthFirstIteratorHandle* outputIterator);
    NrtBool Nrt_SceneNode_CanReach(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode);
    NrtResult Nrt_SceneNode_Destroy(NrtSceneNodeHandle node);

    NrtResult Nrt_SceneNodeSet_Destroy(NrtSceneNodeSetHandle nodeSet);
    size_t Nrt_SceneNodeSet_GetSize(const NrtSceneNodeSetHandle nodeSet);
    NrtResult Nrt_SceneNodeSet_GetSceneNodeFromIndex(const NrtSceneNodeSetHandle nodeSet,
                                                     size_t index,
                                                     NrtSceneNodeHandle* outputSceneNode);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
