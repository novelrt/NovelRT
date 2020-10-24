// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"
#include "NovelRT.Interop/SceneGraph/NovelRTQuadTreeScenePoint.h"
#include "NovelRT.Interop/SceneGraph/NovelRTQuadTreeNode.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"


#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

int32_t NovelRT_QuadTreeNode_create(NovelRTQuadTreeScenePointArray points, NovelRTQuadTreeNode* outputNode, const char** errorMessage) {
  if(points == nullptr || outputNode == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

  std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4> cppArray = *reinterpret_cast<std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>*>(points);
  SceneGraph::QuadTreeNode* cppNode = new SceneGraph::QuadTreeNode(cppArray);
  *outputNode = reinterpret_cast<NovelRTQuadTreeNode>(&cppNode);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_QuadTreeNode_getTopLeft(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage) {
  if(node == nullptr || outputPoint == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

  SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

  SceneGraph::QuadTreeScenePoint* point = cppNode->getTopLeft().get();
  *outputPoint = reinterpret_cast<NovelRTQuadTreeScenePoint>(&point);
  return NOVELRT_SUCCESS;
  }

int32_t NovelRT_QuadTreeNode_getTopRight(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage) {
  if(node == nullptr || outputPoint == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

  SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

  SceneGraph::QuadTreeScenePoint* point = cppNode->getTopRight().get();
  *outputPoint = reinterpret_cast<NovelRTQuadTreeScenePoint>(&point);
  return NOVELRT_SUCCESS;
}


int32_t NovelRT_QuadTreeNode_getBottomLeft(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage) {
  if(node == nullptr || outputPoint == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

  SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

  SceneGraph::QuadTreeScenePoint* point = cppNode->getBottomLeft().get();
  *outputPoint = reinterpret_cast<NovelRTQuadTreeScenePoint>(&point);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_QuadTreeNode_getBottomRight(NovelRTQuadTreeNode node, NovelRTQuadTreeScenePoint* outputPoint, const char** errorMessage) {
  if(node == nullptr || outputPoint == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

  SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

  SceneGraph::QuadTreeScenePoint* point = cppNode->getBottomRight().get();
  *outputPoint = reinterpret_cast<NovelRTQuadTreeScenePoint>(&point);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_QuadTreeScenePointArray_create(NovelRTQuadTreeScenePoint pointOne, NovelRTQuadTreeScenePoint pointTwo, 
    NovelRTQuadTreeScenePoint pointThree, NovelRTQuadTreeScenePoint pointFour, 
    NovelRTQuadTreeScenePointArray* outputArray, const char** errorMessage) {
      if(pointOne == nullptr || pointTwo == nullptr || pointThree == nullptr || pointFour == nullptr || outputArray == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

      std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointOne = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointOne));
      std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointTwo = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointTwo));
      std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointThree = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointThree));
      std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointFour = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointFour));

      std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>* quadTreePoints = new std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>();
      *quadTreePoints = { cppPointOne, cppPointTwo, cppPointThree, cppPointFour };
      *outputArray = reinterpret_cast<NovelRTQuadTreeScenePointArray>(&quadTreePoints);
      return NOVELRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
