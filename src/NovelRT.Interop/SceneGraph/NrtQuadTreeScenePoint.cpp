// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stdint.h>
#include <list>
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneNode.h"
#include "NovelRT.Interop/Maths/NrtGeoVector2F.h"
#include "NovelRT.Interop/SceneGraph/NrtQuadTreeScenePoint.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtResult Nrt_QuadTreeScenePoint_createVector(NrtGeoVector2F position, NrtSceneNode node, NrtQuadTreeScenePoint* outputPoint) {
  if(node == nullptr|| outputPoint == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Maths::GeoVector2F cPosition = *reinterpret_cast<const Maths::GeoVector2F*>(&position);
  std::shared_ptr<SceneGraph::SceneNode> cNode = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
  SceneGraph::QuadTreeScenePoint* cppPoint = new SceneGraph::QuadTreeScenePoint(cPosition, cNode);
  *outputPoint = reinterpret_cast<NrtQuadTreeScenePoint>(&cppPoint);
  return NRT_SUCCESS;
}

NrtResult Nrt_QuadTreeScenePoint_createFloat(float x, float y, NrtSceneNode node, NrtQuadTreeScenePoint* outputPoint) {
  if(node == nullptr|| outputPoint == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  std::shared_ptr<SceneGraph::SceneNode> cNode = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
  SceneGraph::QuadTreeScenePoint* cppPoint = new SceneGraph::QuadTreeScenePoint(x, y, cNode);
  *outputPoint = reinterpret_cast<NrtQuadTreeScenePoint>(&cppPoint);
  return NRT_SUCCESS;  
}


NrtResult Nrt_QuadTreeScenePoint_getSceneNode(NrtQuadTreeScenePoint point, NrtSceneNode* outputNode) {
  if(point == nullptr || outputNode == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  SceneGraph::QuadTreeScenePoint* cppPoint = reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(point);
  std::shared_ptr<SceneGraph::SceneNode> node = cppPoint->getSceneNode();
  *outputNode = reinterpret_cast<NrtSceneNode>(node.get());
  return NRT_SUCCESS;
}


#ifdef __cplusplus
}
#endif
