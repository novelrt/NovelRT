// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNode.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h>
#include <NovelRT.h>
#include <list>
#include <stddef.h>
#include <stdint.h>
using namespace NovelRT;

std::list<std::shared_ptr<SceneGraph::SceneNode>> _sceneNodeCollection;
void (*_voidFunction)(NrtSceneNode) = NULL;
int32_t (*_intFunction)(NrtSceneNode) = NULL;

// Defining internal methods first to prevent compilation issues
void Internal_VoidSceneNodeFunctionInvoker(const std::shared_ptr<SceneGraph::SceneNode> node)
{
    _voidFunction(reinterpret_cast<NrtSceneNode>(node.get()));
}

int32_t Internal_Int32TSceneNodeFunctionInvoker(const std::shared_ptr<SceneGraph::SceneNode> node)
{
    return _intFunction(reinterpret_cast<NrtSceneNode>(node.get()));
}

#ifdef __cplusplus
extern "C"
{
#endif

    // External methods
    NrtSceneNode Nrt_SceneNode_create()
    {
        _sceneNodeCollection.push_back(std::make_shared<SceneGraph::SceneNode>());
        return reinterpret_cast<NrtSceneNode>(_sceneNodeCollection.back().get());
    }

    NrtResult Nrt_SceneNode_getChildren(NrtSceneNode node, NrtSceneNodeSet* outputSet)
    {
        if (node == nullptr || outputSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getChildren();
        *outputSet = reinterpret_cast<NrtSceneNodeSet>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_getParents(NrtSceneNode node, NrtSceneNodeSet* outputSet)
    {
        if (node == nullptr || outputSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getParents();
        *outputSet = reinterpret_cast<NrtSceneNodeSet>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNode_insert(NrtSceneNode node, NrtSceneNode nodeToInsert)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
        return static_cast<int32_t>(
            nodePointer->insert(reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this()));
    }

    NrtBool Nrt_SceneNode_remove(NrtSceneNode node, NrtSceneNode nodeToRemove)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
        return static_cast<int32_t>(
            nodePointer->remove(reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this()));
    }

    NrtBool Nrt_SceneNode_isAdjacent(NrtSceneNode firstNode, NrtSceneNode secondNode)
    {
        auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
        return static_cast<int32_t>(
            nodePointer->isAdjacent(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
    }

    NrtResult Nrt_SceneNode_traverseBreadthFirst(NrtSceneNode node, void (*action)(NrtSceneNode))
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

    NrtResult Nrt_SceneNode_traverseBreadthFirstWithIterator(NrtSceneNode node, int32_t (*action)(NrtSceneNode),
                                                             NrtSceneNodeBreadthFirstIterator* outputIterator)
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
        *outputIterator = reinterpret_cast<NrtSceneNodeBreadthFirstIterator>(itPtr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SceneNode_traverseDepthFirst(NrtSceneNode node, void (*action)(NrtSceneNode))
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

    NrtResult Nrt_SceneNode_traverseDepthFirstWithIterator(NrtSceneNode node, int32_t (*action)(NrtSceneNode),
                                                           NrtSceneNodeDepthFirstIterator* outputIterator)
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
        *outputIterator = reinterpret_cast<NrtSceneNodeDepthFirstIterator>(itPtr);

        return NRT_SUCCESS;
    }

    NrtBool Nrt_SceneNode_canReach(NrtSceneNode firstNode, NrtSceneNode secondNode)
    {
        auto firstNodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
        return static_cast<int32_t>(
            firstNodePointer->canReach(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
    }

    NrtResult Nrt_SceneNode_delete(NrtSceneNode node)
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

    NrtResult Nrt_SceneNodeSet_delete(NrtSceneNodeSet nodeSet)
    {
        if (nodeSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
        return NRT_SUCCESS;
    }

    size_t Nrt_SceneNodeSet_getSize(const NrtSceneNodeSet nodeSet)
    {
        return reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet)->size();
    }

    NrtResult Nrt_SceneNodeSet_getSceneNodeFromIndex(const NrtSceneNodeSet nodeSet, size_t index,
                                                     NrtSceneNode* outputSceneNode)
    {
        if (nodeSet == nullptr || outputSceneNode == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto cNodeSet = reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
        *outputSceneNode = reinterpret_cast<NrtSceneNode&>(cNodeSet[index]);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
