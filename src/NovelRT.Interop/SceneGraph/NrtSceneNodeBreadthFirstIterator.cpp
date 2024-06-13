// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h>
#include <NovelRT/NovelRT.h>

#include <list>

using namespace NovelRT;

int32_t Internal_BreadthFirstIteratorFunctionDelegate(int32_t (*action)(NrtSceneNodeHandle, void* context),
                                                      void* context,
                                                      const std::shared_ptr<SceneGraph::SceneNode>& node)
{
    return action(reinterpret_cast<NrtSceneNodeHandle>(node.get()), context);
}

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeBreadthFirstIterator_Create(NrtSceneNodeHandle node,
                                                       int32_t (*action)(NrtSceneNodeHandle, void* context),
                                                       void* context,
                                                       NrtSceneNodeBreadthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr || action == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        auto func = std::bind(Internal_BreadthFirstIteratorFunctionDelegate, action, context, std::placeholders::_1);
        SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t> iterator =
            SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>(nodePointer, func);
        *outputIterator = reinterpret_cast<NrtSceneNodeBreadthFirstIteratorHandle>(&iterator);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeBreadthFirstIterator_Increment(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        cppIterator->operator++();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeBreadthFirstIterator_PostFixIncrement(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        ++cppIterator; // TODO: is this correct lol?
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNodeBreadthFirstIterator_IsEnd(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>* cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        return static_cast<int32_t>(cppIterator->isEnd());
    }

    NrtBool Nrt_SceneNodeBreadthFirstIterator_IsEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                      NrtSceneNodeBreadthFirstIteratorHandle other)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        auto otherCppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(other);
        return static_cast<int32_t>(*cppIterator == *otherCppIterator);
    }

    NrtBool Nrt_SceneNodeBreadthFirstIterator_IsNotEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                         NrtSceneNodeBreadthFirstIteratorHandle other)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        auto otherCppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(other);
        return static_cast<int32_t>(*cppIterator != *otherCppIterator);
    }

    int32_t Nrt_SceneNodeBreadthFirstIterator_RunFunction(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        return cppIterator->operator*();
    }

#ifdef __cplusplus
}
#endif
