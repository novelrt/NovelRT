// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtRenderObjectNode.h>
#include <NovelRT.h>

#include <list>

using namespace NovelRT;

std::list<std::shared_ptr<Graphics::RenderObject>> _renderObjectNodeCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_RenderObjectNode_create(NrtRenderObjectHandle object, NrtRenderObjectNodeHandle* outputNode)
    {
        if (object == nullptr || outputNode == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        auto ptr = reinterpret_cast<Graphics::RenderObject*>(object);
        std::shared_ptr<Graphics::RenderObject> cppObject = std::shared_ptr<Graphics::RenderObject>(ptr);
        _renderObjectNodeCollection.push_back(cppObject);
        *outputNode = reinterpret_cast<NrtRenderObjectNodeHandle>(new SceneGraph::RenderObjectNode(cppObject));
        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderObjectNode_getRenderObject(NrtRenderObjectNodeHandle node, NrtRenderObjectHandle* outputObject)
    {
        if (node == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        if (outputObject == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        SceneGraph::RenderObjectNode* cppNode = reinterpret_cast<SceneGraph::RenderObjectNode*>(node);
        auto obj = cppNode->getRenderObject();
        *outputObject = reinterpret_cast<NrtRenderObjectHandle>(&obj);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderObjectNode_delete(NrtRenderObjectNodeHandle node)
    {
        if (node == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        auto cppNode = reinterpret_cast<SceneGraph::RenderObjectNode*>(node)->getRenderObject();
        for (auto innerNode : _renderObjectNodeCollection)
        {
            if (innerNode == cppNode)
            {
                _renderObjectNodeCollection.remove(innerNode);
                return NRT_SUCCESS;
            }
        }

        return Nrt_getAlreadyDeletedOrRemovedErrorInternal();
    }

#ifdef __cplusplus
}
#endif
