// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
#define NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QuadTreeScenePointHandle* NovelRTQuadTreeScenePoint;

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
typedef struct NovelRTGeoVector2F;
#endif

#ifndef NOVELRT__INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NovelRTSceneNode;
#endif

int32_t NovelRT_QuadTreeScenePoint_createVector(NovelRTGeoVector2F position, NovelRTSceneNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage);
int32_t NovelRT_QuadTreeScenePoint_createFloat(float x, float y, NovelRTSceneNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage);
int32_t NovelRT_QuadTreeScenePoint_getSceneNode(NovelRTQuadTreeScenePoint point, NovelRTSceneNode* outputNode, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
