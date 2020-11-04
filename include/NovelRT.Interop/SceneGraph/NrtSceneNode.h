// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H

#include <stdint.h>
#include <stddef.h>
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceneNodeHandle* NrtSceneNode;
typedef struct StdSet_SceneNode* NrtSceneNodeSet;
typedef struct BreadthFirstIterator* NrtSceneNodeBreadthFirstIterator;
typedef struct DepthFirstIterator* NrtSceneNodeDepthFirstIterator;

NrtSceneNode Nrt_SceneNode_create();
NrtResult Nrt_SceneNode_getChildren(NrtSceneNode node, NrtSceneNodeSet* outputSet);
NrtResult Nrt_SceneNode_getParents(NrtSceneNode node, NrtSceneNodeSet* outputSet);
NrtResult Nrt_SceneNode_insert(NrtSceneNode node, NrtSceneNode nodeToInsert, int32_t* outputResult);
NrtResult Nrt_SceneNode_remove(NrtSceneNode node, NrtSceneNode nodeToRemove, int32_t* outputResult);
NrtResult Nrt_SceneNode_isAdjacent(NrtSceneNode firstNode, NrtSceneNode secondNode, int32_t* outputResult);
NrtResult Nrt_SceneNode_traverseBreadthFirst(NrtSceneNode node, void(*action)(NrtSceneNode));
NrtResult Nrt_SceneNode_traverseBreadthFirstWithIterator(NrtSceneNode node, int32_t(*action)(NrtSceneNode), NrtSceneNodeBreadthFirstIterator* outputIterator);
NrtResult Nrt_SceneNode_traverseDepthFirst(NrtSceneNode node, void(*action)(NrtSceneNode));
NrtResult Nrt_SceneNode_traverseDepthFirstWithIterator(NrtSceneNode node, int32_t(*action)(NrtSceneNode), NrtSceneNodeDepthFirstIterator* outputIterator);
NrtResult Nrt_SceneNode_canReach(NrtSceneNode firstNode, NrtSceneNode secondNode, int32_t* outputResult);
NrtResult Nrt_SceneNode_delete(NrtSceneNode node);

NrtResult Nrt_SceneNodeSet_delete(NrtSceneNodeSet nodeSet);
NrtResult Nrt_SceneNodeSet_getSize(const NrtSceneNodeSet nodeSet, size_t* outputSize);
NrtResult Nrt_SceneNodeSet_getSceneNodeFromIndex(const NrtSceneNodeSet nodeSet, size_t index, NrtSceneNode* outputSceneNode);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
