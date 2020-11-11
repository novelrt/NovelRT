// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stdint.h>
#include <list>
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneNode.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.h"
using namespace NovelRT;

int32_t(*_function)(NrtSceneNode) = NULL;

int32_t Internal_BreadthFirstIteratorFunctionDelegate(const std::shared_ptr<SceneGraph::SceneNode>& node) {
  return _function(reinterpret_cast<NrtSceneNode>(node.get()));
}

#ifdef __cplusplus
extern "C" {
#endif

NrtResult Nrt_SceneNodeBreadthFirstIterator_create(NrtSceneNode node, int32_t(*func)(NrtSceneNode), NrtSceneNodeBreadthFirstIterator* outputIterator) {
  if(node == nullptr|| func == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
    
  auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

  _function = func;
  SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t> iterator = SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>(nodePointer, Internal_BreadthFirstIteratorFunctionDelegate);
  *outputIterator = reinterpret_cast<NrtSceneNodeBreadthFirstIterator>(&iterator); 
  return NRT_SUCCESS;
}

NrtResult Nrt_SceneNodeBreadthFirstIterator_increment(NrtSceneNodeBreadthFirstIterator iterator) {
  if(iterator == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
  cppIterator->operator++();
  return NRT_SUCCESS;
}

NrtResult Nrt_SceneNodeBreadthFirstIterator_postFixIncrement(NrtSceneNodeBreadthFirstIterator iterator) {
  if(iterator == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
  ++cppIterator; //TODO: is this correct lol?
  return NRT_SUCCESS;
}

NrtResult Nrt_SceneNodeBreadthFirstIterator_isEnd(NrtSceneNodeBreadthFirstIterator iterator, int32_t* outputResult) {
  if(iterator == nullptr || outputResult == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
      
  SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>* cppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
      
  *outputResult = cppIterator->isEnd();
  return NRT_SUCCESS;
}

NrtResult Nrt_SceneNodeBreadthFirstIterator_isEqual(NrtSceneNodeBreadthFirstIterator iterator, NrtSceneNodeBreadthFirstIterator other, int32_t* outputResult) {
  if(iterator == nullptr || outputResult == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
  auto otherCppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(other);

  *outputResult = (*cppIterator == *otherCppIterator);
  return NRT_SUCCESS;
}

NrtResult Nrt_SceneNodeBreadthFirstIterator_isNotEqual(NrtSceneNodeBreadthFirstIterator iterator, NrtSceneNodeBreadthFirstIterator other, int32_t* outputResult) {
  if(iterator == nullptr || outputResult == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
  auto otherCppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(other);

  *outputResult = (*cppIterator != *otherCppIterator);
  return NRT_SUCCESS;
}

NrtResult Nrt_SceneNodeBreadthFirstIterator_runFunction(NrtSceneNodeBreadthFirstIterator iterator, int32_t* outputResult) {
  if(iterator == nullptr || outputResult == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
  *outputResult = cppIterator->operator*();
  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
