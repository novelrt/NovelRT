// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNode.h>
#include <NovelRT/NovelRT.h>

#include <list>

using namespace NovelRT;

std::list<std::shared_ptr<SceneGraph::SceneNode>> _sceneNodeCollection;

void Internal_VoidSceneNodeFunctionInvoker(void (*action)(NrtSceneNodeHandle, void*),
                                           void* context,
                                           const std::shared_ptr<SceneGraph::SceneNode> node)
{
    action(reinterpret_cast<NrtSceneNodeHandle>(node.get()), context);
}

int32_t Internal_Int32TSceneNodeFunctionInvoker(int32_t (*action)(NrtSceneNodeHandle, void*),
                                                void* context,
                                                const std::shared_ptr<SceneGraph::SceneNode> node)
{
    return action(reinterpret_cast<NrtSceneNodeHandle>(node.get()), context);
}

#ifdef __cplusplus
extern "C"
{
#endif

    // External methods
    NrtSceneNodeHandle Nrt_SceneNode_Create()
    {
        _sceneNodeCollection.push_back(std::make_shared<SceneGraph::SceneNode>());
        return reinterpret_cast<NrtSceneNodeHandle>(_sceneNodeCollection.back().get());
    }

    NrtResult Nrt_SceneNode_GetChildren(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputSet == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getChildren();
        *outputSet = reinterpret_cast<NrtSceneNodeSetHandle>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_GetParents(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputSet == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getParents();
        *outputSet = reinterpret_cast<NrtSceneNodeSetHandle>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNode_Insert(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToInsert)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
        return static_cast<int32_t>(
            nodePointer->insert(reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this()));
    }

    NrtBool Nrt_SceneNode_Remove(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToRemove)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
        return static_cast<int32_t>(
            nodePointer->remove(reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this()));
    }

    NrtBool Nrt_SceneNode_IsAdjacent(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
        return static_cast<int32_t>(
            nodePointer->isAdjacent(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
    }

    NrtResult Nrt_SceneNode_TraverseBreadthFirst(NrtSceneNodeHandle node,
                                                 void (*action)(NrtSceneNodeHandle, void*),
                                                 void* context)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (action == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
        auto func = std::bind(Internal_VoidSceneNodeFunctionInvoker, action, context, std::placeholders::_1);
        nodePointer->traverseBreadthFirst(func);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_TraverseBreadthFirstWithIterator(NrtSceneNodeHandle node,
                                                             int32_t (*action)(NrtSceneNodeHandle, void*),
                                                             void* context,
                                                             NrtSceneNodeBreadthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr || action == nullptr || outputIterator == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        auto func = std::bind(Internal_Int32TSceneNodeFunctionInvoker, action, context, std::placeholders::_1);
        SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>* itPtr =
            new SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>(nodePointer, func);
        *outputIterator = reinterpret_cast<NrtSceneNodeBreadthFirstIteratorHandle>(itPtr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_TraverseDepthFirst(NrtSceneNodeHandle node,
                                               void (*action)(NrtSceneNodeHandle, void*),
                                               void* context)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (action == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        auto func = std::bind(Internal_VoidSceneNodeFunctionInvoker, action, context, std::placeholders::_1);
        nodePointer->traverseDepthFirst(func);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_TraverseDepthFirstWithIterator(NrtSceneNodeHandle node,
                                                           int32_t (*action)(NrtSceneNodeHandle, void*),
                                                           void* context,
                                                           NrtSceneNodeDepthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (action == nullptr || outputIterator == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        auto func = std::bind(Internal_Int32TSceneNodeFunctionInvoker, action, context, std::placeholders::_1);
        SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>* itPtr =
            new SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>(nodePointer, func);
        *outputIterator = reinterpret_cast<NrtSceneNodeDepthFirstIteratorHandle>(itPtr);

        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNode_CanReach(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode)
    {
        auto firstNodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
        return static_cast<int32_t>(
            firstNodePointer->canReach(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
    }

    NrtResult Nrt_SceneNode_Destroy(NrtSceneNodeHandle node)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
        if (std::find(_sceneNodeCollection.begin(), _sceneNodeCollection.end(), nodePointer) ==
            _sceneNodeCollection.end())
        {
            Nrt_SetErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }

        _sceneNodeCollection.remove(nodePointer);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeSet_Destroy(NrtSceneNodeSetHandle nodeSet)
    {
        if (nodeSet == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
        return NRT_SUCCESS;
    }

    size_t Nrt_SceneNodeSet_GetSize(const NrtSceneNodeSetHandle nodeSet)
    {
        return reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet)->size();
    }

    NrtResult Nrt_SceneNodeSet_GetSceneNodeFromIndex(const NrtSceneNodeSetHandle nodeSet,
                                                     size_t index,
                                                     NrtSceneNodeHandle* outputSceneNode)
    {
        if (nodeSet == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputSceneNode == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cNodeSet = reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
        *outputSceneNode = reinterpret_cast<NrtSceneNodeHandle&>(cNodeSet[index]);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
