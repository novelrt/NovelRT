// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
#define NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H

#include <stdint.h>
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Maths/NrtGeoVector2F.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneGraphTypeDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

NrtResult Nrt_QuadTreeScenePoint_createVector(NrtGeoVector2F position, NrtSceneNode node, NrtQuadTreeScenePoint* outputPoint);
NrtResult Nrt_QuadTreeScenePoint_createFloat(float x, float y, NrtSceneNode node, NrtQuadTreeScenePoint* outputPoint);
NrtResult Nrt_QuadTreeScenePoint_getSceneNode(NrtQuadTreeScenePoint point, NrtSceneNode* outputNode);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_QUADTREESCENEPOINT_H
