// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include <list>
#include "NovelRT.Interop/SceneGraph/NovelRTRenderObjectNode.h"
#include "NovelRT.Interop/Graphics/NovelRTGraphicsTypeDefs.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"
using namespace NovelRT;

std::list<std::shared_ptr<Graphics::RenderObject>> _renderObjectNodeCollection;


#ifdef __cplusplus
extern "C" {
#endif

int32_t NovelRT_RenderObjectNode_create(NovelRTRenderObject object, NovelRTRenderObjectNode* outputNode, const char** errorMessage) {
    if(object == nullptr|| outputNode == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto ptr = reinterpret_cast<Graphics::RenderObject*>(object);
    std::shared_ptr<Graphics::RenderObject> cppObject = std::shared_ptr<Graphics::RenderObject>(ptr);
    _renderObjectNodeCollection.push_back(cppObject);
    *outputNode = reinterpret_cast<NovelRTRenderObjectNode>(new SceneGraph::RenderObjectNode(cppObject));
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_RenderObjectNode_getRenderObject(NovelRTRenderObjectNode node, NovelRTRenderObject* outputObject, const char** errorMessage) {
    if(node == nullptr|| outputObject == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    SceneGraph::RenderObjectNode* cppNode = reinterpret_cast<SceneGraph::RenderObjectNode*>(node);
    auto obj = cppNode->getRenderObject();
    *outputObject = reinterpret_cast<NovelRTRenderObject>(&obj);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_RenderObjectNode_delete(NovelRTRenderObjectNode node, const char** errorMessage) {
    if(node == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto cppNode = reinterpret_cast<SceneGraph::RenderObjectNode*>(node)->getRenderObject();
    for (auto innerNode : _renderObjectNodeCollection) {
        if (innerNode == cppNode) {
            _renderObjectNodeCollection.remove(innerNode);
        }
    }
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
