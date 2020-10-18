// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include <list>
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNodeDepthFirstIterator.h"
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"
using namespace NovelRT;

int32_t(*_depthFunction)(NovelRTSceneNode) = NULL;

int32_t Internal_DepthFirstIteratorFunctionDelegate(const std::shared_ptr<SceneGraph::SceneNode>& node) {
    return _depthFunction(reinterpret_cast<NovelRTSceneNode>(node.get()));
}

#ifdef __cplusplus
extern "C" {
#endif

int32_t NovelRT_SceneNodeDepthFirstIterator_create(NovelRTSceneNode node, int32_t(*func)(NovelRTSceneNode), NovelRTSceneNodeDepthFirstIterator* outputIterator, const char** errorMessage) {
    if(node == nullptr|| func == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }
    
    auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

    _depthFunction = func;
    SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t> iterator = SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>(nodePointer, Internal_DepthFirstIteratorFunctionDelegate);
    *outputIterator = reinterpret_cast<NovelRTSceneNodeDepthFirstIterator>(&iterator); 

    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeDepthFirstIterator_increment(NovelRTSceneNodeDepthFirstIterator iterator, const char** errorMessage) {
    if(iterator == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
    cppIterator->operator++();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeDepthFirstIterator_postFixIncrement(NovelRTSceneNodeDepthFirstIterator iterator, const char** errorMessage) {
    if(iterator == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
    ++cppIterator;
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeDepthFirstIterator_isEnd(NovelRTSceneNodeDepthFirstIterator iterator, int32_t* outputResult, const char** errorMessage) {
  if(iterator == nullptr || outputResult == nullptr) {
        if(errorMessage != nullptr) {
          *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
      }
      
      SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>* cppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
      
      *outputResult = cppIterator->isEnd();
      return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeDepthFirstIterator_isEqual(NovelRTSceneNodeDepthFirstIterator iterator, NovelRTSceneNodeDepthFirstIterator other, int32_t* outputResult, const char** errorMessage) {
    if(iterator == nullptr || outputResult == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
    auto otherCppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(other);

    *outputResult = (*cppIterator == *otherCppIterator);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeDepthFirstIterator_isNotEqual(NovelRTSceneNodeDepthFirstIterator iterator, NovelRTSceneNodeDepthFirstIterator other, int32_t* outputResult, const char** errorMessage) {
    if(iterator == nullptr || outputResult == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
    auto otherCppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(other);

    *outputResult = (*cppIterator != *otherCppIterator);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeDepthFirstIterator_runFunction(NovelRTSceneNodeDepthFirstIterator iterator, int32_t* outputResult, const char** errorMessage) {
    if(iterator == nullptr || outputResult == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }
     auto cppIterator = reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
     *outputResult = cppIterator->operator*();
     return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
