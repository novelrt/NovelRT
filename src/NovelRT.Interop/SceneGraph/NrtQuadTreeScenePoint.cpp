// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtQuadTreeScenePoint.h>
#include <NovelRT/NovelRT.h>

#include <list>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtResult Nrt_QuadTreeScenePoint_createVector(NrtGeoVector2F position,
                                                  NrtSceneNodeHandle node,
                                                  NrtQuadTreeScenePointHandle* outputPoint)
    {
        if (node == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Maths::GeoVector2F cPosition = *reinterpret_cast<const Maths::GeoVector2F*>(&position);
        std::shared_ptr<SceneGraph::SceneNode> cNode =
            reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
        SceneGraph::QuadTreeScenePoint* cppPoint = new SceneGraph::QuadTreeScenePoint(cPosition, cNode);
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePointHandle>(&cppPoint);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeScenePoint_createFloat(float x,
                                                 float y,
                                                 NrtSceneNodeHandle node,
                                                 NrtQuadTreeScenePointHandle* outputPoint)
    {
        if (node == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::shared_ptr<SceneGraph::SceneNode> cNode =
            reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
        SceneGraph::QuadTreeScenePoint* cppPoint = new SceneGraph::QuadTreeScenePoint(x, y, cNode);
        *outputPoint = reinterpret_cast<NrtQuadTreeScenePointHandle>(&cppPoint);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTreeScenePoint_getSceneNode(NrtQuadTreeScenePointHandle point, NrtSceneNodeHandle* outputNode)
    {
        if (point == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputNode == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        SceneGraph::QuadTreeScenePoint* cppPoint = reinterpret_cast<SceneGraph::QuadTreeScenePoint*>(point);
        std::shared_ptr<SceneGraph::SceneNode> node = cppPoint->getSceneNode();
        *outputNode = reinterpret_cast<NrtSceneNodeHandle>(node.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
