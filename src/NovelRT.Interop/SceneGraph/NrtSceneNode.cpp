// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNode.h>
#include <NovelRT.h>

#include <list>

using namespace NovelRT;

std::list<std::shared_ptr<SceneGraph::SceneNode>> _sceneNodeCollection;
void (*_voidFunction)(NrtSceneNodeHandle) = NULL;
int32_t (*_intFunction)(NrtSceneNodeHandle) = NULL;

// Defining internal methods first to prevent compilation issues
void Internal_VoidSceneNodeFunctionInvoker(const std::shared_ptr<SceneGraph::SceneNode> node)
{
    _voidFunction(reinterpret_cast<NrtSceneNodeHandle>(node.get()));
}

int32_t Internal_Int32TSceneNodeFunctionInvoker(const std::shared_ptr<SceneGraph::SceneNode> node)
{
    return _intFunction(reinterpret_cast<NrtSceneNodeHandle>(node.get()));
}

#ifdef __cplusplus
extern "C"
{
#endif

    // External methods
    NrtSceneNodeHandle Nrt_SceneNode_create()
    {
        _sceneNodeCollection.push_back(std::make_shared<SceneGraph::SceneNode>());
        return reinterpret_cast<NrtSceneNodeHandle>(_sceneNodeCollection.back().get());
    }

    NrtResult Nrt_SceneNode_getChildren(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet)
    {
        if (node == nullptr || outputSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getChildren();
        *outputSet = reinterpret_cast<NrtSceneNodeSetHandle>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_getParents(NrtSceneNodeHandle node, NrtSceneNodeSetHandle* outputSet)
    {
        if (node == nullptr || outputSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getParents();
        *outputSet = reinterpret_cast<NrtSceneNodeSetHandle>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNode_insert(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToInsert)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
        return static_cast<int32_t>(
            nodePointer->insert(reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this()));
    }

    NrtBool Nrt_SceneNode_remove(NrtSceneNodeHandle node, NrtSceneNodeHandle nodeToRemove)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
        return static_cast<int32_t>(
            nodePointer->remove(reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this()));
    }

    NrtBool Nrt_SceneNode_isAdjacent(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
        return static_cast<int32_t>(
            nodePointer->isAdjacent(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
    }

    NrtResult Nrt_SceneNode_traverseBreadthFirst(NrtSceneNodeHandle node, void (*action)(NrtSceneNodeHandle))
    {
        if (node == nullptr || action == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
        _voidFunction = action;
        nodePointer->traverseBreadthFirst(Internal_VoidSceneNodeFunctionInvoker);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_traverseBreadthFirstWithIterator(NrtSceneNodeHandle node,
                                                             int32_t (*action)(NrtSceneNodeHandle),
                                                             NrtSceneNodeBreadthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr || action == nullptr || outputIterator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        _intFunction = action;
        SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>* itPtr =
            new SceneGraph::SceneNode::breadth_first_traversal_result_iterator<int32_t>(
                nodePointer, Internal_Int32TSceneNodeFunctionInvoker);
        *outputIterator = reinterpret_cast<NrtSceneNodeBreadthFirstIteratorHandle>(itPtr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_traverseDepthFirst(NrtSceneNodeHandle node, void (*action)(NrtSceneNodeHandle))
    {
        if (node == nullptr || action == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        _voidFunction = action;
        nodePointer->traverseDepthFirst(Internal_VoidSceneNodeFunctionInvoker);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_traverseDepthFirstWithIterator(NrtSceneNodeHandle node,
                                                           int32_t (*action)(NrtSceneNodeHandle),
                                                           NrtSceneNodeDepthFirstIteratorHandle* outputIterator)
    {
        if (node == nullptr || action == nullptr || outputIterator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();

        _intFunction = action;
        SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>* itPtr =
            new SceneGraph::SceneNode::depth_first_traversal_result_iterator<int32_t>(
                nodePointer, Internal_Int32TSceneNodeFunctionInvoker);
        *outputIterator = reinterpret_cast<NrtSceneNodeDepthFirstIteratorHandle>(itPtr);

        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNode_canReach(NrtSceneNodeHandle firstNode, NrtSceneNodeHandle secondNode)
    {
        auto firstNodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
        return static_cast<int32_t>(
            firstNodePointer->canReach(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
    }

    NrtResult Nrt_SceneNode_delete(NrtSceneNodeHandle node)
    {
        if (node == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
        if (std::find(_sceneNodeCollection.begin(), _sceneNodeCollection.end(), nodePointer) ==
            _sceneNodeCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }

        _sceneNodeCollection.remove(nodePointer);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNodeSet_delete(NrtSceneNodeSetHandle nodeSet)
    {
        if (nodeSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
        return NRT_SUCCESS;
    }

    size_t Nrt_SceneNodeSet_getSize(const NrtSceneNodeSetHandle nodeSet)
    {
        return reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet)->size();
    }

    NrtResult Nrt_SceneNodeSet_getSceneNodeFromIndex(const NrtSceneNodeSetHandle nodeSet,
                                                     size_t index,
                                                     NrtSceneNodeHandle* outputSceneNode)
    {
        if (nodeSet == nullptr || outputSceneNode == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto cNodeSet = reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
        *outputSceneNode = reinterpret_cast<NrtSceneNodeHandle&>(cNodeSet[index]);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
