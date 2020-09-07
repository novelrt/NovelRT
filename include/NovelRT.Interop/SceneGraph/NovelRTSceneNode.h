// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceneNodeHandle* NovelRTSceneNode;
typedef struct StdSet_SceneNode* NovelRTSceneNodeSet;

NovelRTSceneNode NovelRT_SceneNode_create();
int32_t NovelRT_SceneNode_getChildren(NovelRTSceneNode node, NovelRTSceneNodeSet* outputSet, const char** errorMessage);
int32_t NovelRT_SceneNode_getParents(NovelRTSceneNode node, NovelRTSceneNodeSet* outputSet, const char** errorMessage);
int32_t NovelRT_SceneNode_insert(NovelRTSceneNode node, NovelRTSceneNode nodeToInsert, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNode_remove(NovelRTSceneNode node, NovelRTSceneNode nodeToRemove, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNode_isAdjacent(NovelRTSceneNode firstNode, NovelRTSceneNode secondNode, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNode_traverseBreadthFirst(NovelRTSceneNode node, void(*action)(NovelRTSceneNode), const char** errorMessage);
int32_t NovelRT_SceneNode_traverseDepthFirst(NovelRTSceneNode node, void(*action)(NovelRTSceneNode), const char** errorMessage);
int32_t NovelRT_SceneNode_canReach(NovelRTSceneNode firstNode, NovelRTSceneNode secondNode, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNode_delete(NovelRTSceneNode node, const char** errorMessage);

int32_t NovelRT_SceneNodeSet_delete(NovelRTSceneNodeSet nodeSet, const char** errorMessage);
int32_t NovelRT_SceneNodeSet_getSize(const NovelRTSceneNodeSet nodeSet, size_t* outputSize, const char** errorMessage);
int32_t NovelRT_SceneNodeSet_getSceneNodeFromIndex(const NovelRTSceneNodeSet nodeSet, size_t index, NovelRTSceneNode* outputSceneNode, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
