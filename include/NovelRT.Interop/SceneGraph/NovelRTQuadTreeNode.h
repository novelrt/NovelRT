// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QuadTreeNode_H
#define NOVELRT_INTEROP_SCENEGRAPH_QuadTreeNode_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QuadTreeNodeHandle* NovelRTQuadTreeNode;
typedef struct QuadTreeScenePointArray* NovelRTQuadTreeScenePointArray;

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
typedef struct QuadTreeScenePointHandle* NovelRTQuadTreeScenePoint;
#endif

#ifndef NOVELRT__INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NovelRTSceneNode;
#endif

int32_t NovelRT_QuadTreeNode_create(NovelRTQuadTreeScenePointArray points, NovelRTQuadTreeNode* outputPoint, const char** errorMessage);
int32_t NovelRT_QuadTreeNode_getTopLeft(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage);
int32_t NovelRT_QuadTreeNode_getTopRight(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage);
int32_t NovelRT_QuadTreeNode_getBottomLeft(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage);
int32_t NovelRT_QuadTreeNode_getBottomRight(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage);

int32_t NovelRT_QuadTreeScenePointArray_create(NovelRTQuadTreeScenePoint pointOne, NovelRTQuadTreeScenePoint pointTwo, 
    NovelRTQuadTreeScenePoint pointThree, NovelRTQuadTreeScenePoint pointFour, 
    NovelRTQuadTreeScenePointArray* outputArray, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_QuadTreeNode_H
