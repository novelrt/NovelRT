// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSceneNodeHandle Nrt_SceneNode_create();
    NrtResult Nrt_SceneNode_getChildren(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet);
    NrtResult Nrt_SceneNode_getParents(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet);
    NrtBool Nrt_SceneNode_insert(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToInsert);
    NrtBool Nrt_SceneNode_remove(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToRemove);
    NrtBool Nrt_SceneNode_isAdjacent(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode);
    NrtResult Nrt_SceneNode_traverseBreadthFirst(NrtSceneNodeHandle node,
                                                 void (*action)(NrtSceneNodeHandle, void*),
                                                 void* context);
    NrtResult Nrt_SceneNode_traverseBreadthFirstWithIterator(NrtSceneNodeHandle node,
                                                             int32_t (*action)(NrtSceneNodeHandle, void*),
                                                             void* context,
                                                             NrtSceneNodeBreadthFirstIteratorHandle* outputIterator);
    NrtResult Nrt_SceneNode_traverseDepthFirst(NrtSceneNodeHandle node,
                                               void (*action)(NrtSceneNodeHandle, void*),
                                               void* context);
    NrtResult Nrt_SceneNode_traverseDepthFirstWithIterator(NrtSceneNodeHandle node,
                                                           int32_t (*action)(NrtSceneNodeHandle, void*),
                                                           void* context,
                                                           NrtSceneNodeDepthFirstIteratorHandle* outputIterator);
    NrtBool Nrt_SceneNode_canReach(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode);
    NrtResult Nrt_SceneNode_delete(NrtSceneNodeHandle node);

    NrtResult Nrt_SceneNodeSet_delete(NrtSceneNodeSetHandle nodeSet);
    size_t Nrt_SceneNodeSet_getSize(const NrtSceneNodeSetHandle nodeSet);
    NrtResult Nrt_SceneNodeSet_getSceneNodeFromIndex(const NrtSceneNodeSetHandle nodeSet,
                                                     size_t index,
                                                     NrtSceneNodeHandle* outputSceneNode);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
