// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h>
#include <NovelRT.h>

#include <list>

using namespace NovelRT;

int32_t (*_function)(NrtSceneNodeHandle) = NULL;

int32_t Internal_BreadthFirstIteratorFunctionDelegate(const std::shared_ptr<SceneGraph::SceneNode>& node)
{
    return _function(reinterpret_cast<NrtSceneNodeHandle>(node.get()));
}

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeBreadthFirstIterator_create(NrtSceneNodeHandle node,
                                                       int32_t (*func)(NrtSceneNodeHandle),
                                                       NrtSceneNodeBreadthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        _function = func;
        SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t> iterator =
            SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>(
                nodePointer, Internal_BreadthFirstIteratorFunctionDelegate);
        *outputIterator = reinterpret_cast<NrtSceneNodeBreadthFirstIteratorHandle>(&iterator);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeBreadthFirstIterator_increment(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        cppIterator->operator++();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeBreadthFirstIterator_postFixIncrement(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        ++cppIterator; // TODO: is this correct lol?
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNodeBreadthFirstIterator_isEnd(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>* cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        return static_cast<int32_t>(cppIterator->isEnd());
    }

    NrtBool Nrt_SceneNodeBreadthFirstIterator_isEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                      NrtSceneNodeBreadthFirstIteratorHandle other)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        auto otherCppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(other);
        return static_cast<int32_t>(*cppIterator == *otherCppIterator);
    }

    NrtBool Nrt_SceneNodeBreadthFirstIterator_isNotEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                         NrtSceneNodeBreadthFirstIteratorHandle other)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        auto otherCppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(other);
        return static_cast<int32_t>(*cppIterator != *otherCppIterator);
    }

    int32_t Nrt_SceneNodeBreadthFirstIterator_runFunction(NrtSceneNodeBreadthFirstIteratorHandle iterator)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>*>(iterator);
        return cppIterator->operator*();
    }

#ifdef __cplusplus
}
#endif
