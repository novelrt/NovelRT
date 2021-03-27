// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNodeDepthFirstIterator.h>

#include <list>

using namespace NovelRT;

int32_t (*_depthFunction)(NrtSceneNodeHandle) = NULL;

int32_t Internal_DepthFirstIteratorFunctionDelegate(const std::shared_ptr<SceneGraph::SceneNode>& node)
{
    return _depthFunction(reinterpret_cast<NrtSceneNodeHandle>(node.get()));
}

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeDepthFirstIterator_create(NrtSceneNodeHandle node,
                                                     int32_t (*func)(NrtSceneNodeHandle),
                                                     NrtSceneNodeDepthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        _depthFunction = func;
        SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t> iterator =
            SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>(
                nodePointer, Internal_DepthFirstIteratorFunctionDelegate);
        *outputIterator = reinterpret_cast<NrtSceneNodeDepthFirstIteratorHandle>(&iterator);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeDepthFirstIterator_increment(NrtSceneNodeDepthFirstIteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
        cppIterator->operator++();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeDepthFirstIterator_postFixIncrement(NrtSceneNodeDepthFirstIteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
        ++cppIterator;
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNodeDepthFirstIterator_isEnd(NrtSceneNodeDepthFirstIteratorHandle iterator)
    {
        SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>* cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
        return static_cast<int32_t>(cppIterator->isEnd());
    }

    NrtBool Nrt_SceneNodeDepthFirstIterator_isEqual(NrtSceneNodeDepthFirstIteratorHandle iterator,
                                                    NrtSceneNodeDepthFirstIteratorHandle other)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
        auto otherCppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(other);
        return static_cast<int32_t>(*cppIterator == *otherCppIterator);
    }

    NrtBool Nrt_SceneNodeDepthFirstIterator_isNotEqual(NrtSceneNodeDepthFirstIteratorHandle iterator,
                                                       NrtSceneNodeDepthFirstIteratorHandle other)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
        auto otherCppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(other);
        return static_cast<int32_t>(*cppIterator != *otherCppIterator);
    }

    int32_t Nrt_SceneNodeDepthFirstIterator_runFunction(NrtSceneNodeDepthFirstIteratorHandle iterator)
    {
        auto cppIterator =
            reinterpret_cast<SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>*>(iterator);
        return cppIterator->operator*();
    }

#ifdef __cplusplus
}
#endif
