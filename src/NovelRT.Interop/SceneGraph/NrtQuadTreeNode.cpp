// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtQuadTreeNode.h>
#include <NovelRT/NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtResult Nrt_QuadTreeNode_Create(NrtQuadTreeScenePointArrayHandle points, NrtQuadTreeNodeHandle* outputNode)
    {
        if (points == nullptr || outputNode == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4> cppArray =
            *reinterpret_cast<std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>*>(points);
        SceneGraph::QuadTreeNode* cppNode = new SceneGraph::QuadTreeNode(cppArray);
        *outputNode = reinterpret_cast<NrtQuadTreeNodeHandle>(&cppNode);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_GetTopLeft(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputPoint == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getTopLeft().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePointHandle>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_GetTopRight(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputPoint == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getTopRight().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePointHandle>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_GetBottomLeft(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputPoint == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getBottomLeft().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePointHandle>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_GetBottomRight(NrtQuadTreeNodeHandle node, NrtQuadTreeScenePointHandle* outputPoint)
    {
        if (node == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputPoint == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getBottomRight().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePointHandle>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeScenePointArray_Create(NrtQuadTreeScenePointHandle pointOne,
                                                 NrtQuadTreeScenePointHandle pointTwo,
                                                 NrtQuadTreeScenePointHandle pointThree,
                                                 NrtQuadTreeScenePointHandle pointFour,
                                                 NrtQuadTreeScenePointArrayHandle* outputArray)
    { // TODO: can we not make this read nicer?
        if (pointOne == nullptr || pointTwo == nullptr || pointThree == nullptr || pointFour == nullptr ||
            outputArray == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointOne = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(
            reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointOne));
        std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointTwo = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(
            reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointTwo));
        std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointThree = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(
            reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointThree));
        std::shared_ptr<SceneGraph::QuadTreeScenePoint> cppPointFour = std::shared_ptr<SceneGraph::QuadTreeScenePoint>(
            reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(pointFour));

        std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>* quadTreePoints =
            new std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>();
        *quadTreePoints = {cppPointOne, cppPointTwo, cppPointThree, cppPointFour};
        *outputArray = reinterpret_cast<NrtQuadTreeScenePointArrayHandle>(&quadTreePoints);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
