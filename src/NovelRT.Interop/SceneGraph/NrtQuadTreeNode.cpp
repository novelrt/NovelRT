// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/SceneGraph/NrtQuadTreeNode.h>
#include <NovelRT.Interop/SceneGraph/NrtQuadTreeScenePoint.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNode.h>
#include <NovelRT.h>
#include <stdint.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtResult Nrt_QuadTreeNode_create(NrtQuadTreeScenePointArray points, NrtQuadTreeNode* outputNode)
    {
        if (points == nullptr || outputNode == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4> cppArray =
            *reinterpret_cast<std::array<std::shared_ptr<SceneGraph::QuadTreeScenePoint>, 4>*>(points);
        SceneGraph::QuadTreeNode* cppNode = new SceneGraph::QuadTreeNode(cppArray);
        *outputNode = reinterpret_cast<NrtQuadTreeNode>(&cppNode);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_getTopLeft(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint)
    {
        if (node == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getTopLeft().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePoint>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_getTopRight(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint)
    {
        if (node == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getTopRight().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePoint>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_getBottomLeft(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint)
    {
        if (node == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getBottomLeft().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePoint>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeNode_getBottomRight(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint)
    {
        if (node == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        SceneGraph::QuadTreeNode* cppNode = reinterpret_cast<SceneGraph::QuadTreeNode*>(node);

        SceneGraph::QuadTreeScenePoint* point = cppNode->getBottomRight().get();
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePoint>(&point);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeScenePointArray_create(NrtQuadTreeScenePoint pointOne, NrtQuadTreeScenePoint pointTwo,
                                                 NrtQuadTreeScenePoint pointThree, NrtQuadTreeScenePoint pointFour,
                                                 NrtQuadTreeScenePointArray* outputArray)
    { // TODO: can we not make this read nicer?
        if (pointOne == nullptr || pointTwo == nullptr || pointThree == nullptr || pointFour == nullptr ||
            outputArray == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
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
        *outputArray = reinterpret_cast<NrtQuadTreeScenePointArray>(&quadTreePoints);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
