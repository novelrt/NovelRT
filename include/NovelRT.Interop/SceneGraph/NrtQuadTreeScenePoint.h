// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
#define NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H

#include <stdint.h>

//TODO:This is redundant. This header already has include guards.
#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
#include "../Maths/NrtGeoVector2F.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QuadTreeScenePointHandle* NrtQuadTreeScenePoint;


#ifndef NOVELRT__INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NrtSceneNode;
#endif

int32_t Nrt_QuadTreeScenePoint_createVector(NrtGeoVector2F position, NrtSceneNode node, NrtQuadTreeScenePoint* outputPoint);
int32_t Nrt_QuadTreeScenePoint_createFloat(float x, float y, NrtSceneNode node, NrtQuadTreeScenePoint* outputPoint);
int32_t Nrt_QuadTreeScenePoint_getSceneNode(NrtQuadTreeScenePoint point, NrtSceneNode* outputNode);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
