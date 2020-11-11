// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include <list>
#include "NovelRT.Interop/Graphics/NrtGraphicsTypedefs.h"
#include "NovelRT.Interop/SceneGraph/NrtRenderObjectNode.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.h"
using namespace NovelRT;

std::list<std::shared_ptr<Graphics::RenderObject>> _renderObjectNodeCollection;


#ifdef __cplusplus
extern "C" {
#endif

NrtResult Nrt_RenderObjectNode_create(NrtRenderObject object, NovelRTRenderObjectNode* outputNode) {
  if(object == nullptr|| outputNode == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto ptr = reinterpret_cast<Graphics::RenderObject*>(object);
  std::shared_ptr<Graphics::RenderObject> cppObject = std::shared_ptr<Graphics::RenderObject>(ptr);
  _renderObjectNodeCollection.push_back(cppObject);
  *outputNode = reinterpret_cast<NovelRTRenderObjectNode>(new SceneGraph::RenderObjectNode(cppObject));
  return NRT_SUCCESS;
}

NrtResult Nrt_RenderObjectNode_getRenderObject(NovelRTRenderObjectNode node, NrtRenderObject* outputObject) {
  if(node == nullptr|| outputObject == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  SceneGraph::RenderObjectNode* cppNode = reinterpret_cast<SceneGraph::RenderObjectNode*>(node);
  auto obj = cppNode->getRenderObject();
  *outputObject = reinterpret_cast<NrtRenderObject>(&obj);
  return NRT_SUCCESS;
}

NrtResult Nrt_RenderObjectNode_delete(NovelRTRenderObjectNode node) {
  if(node == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto cppNode = reinterpret_cast<SceneGraph::RenderObjectNode*>(node)->getRenderObject();
  for (auto innerNode : _renderObjectNodeCollection) {
    if (innerNode == cppNode) {
      _renderObjectNodeCollection.remove(innerNode);
      return NRT_SUCCESS;
    }
  }

  Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
  return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
}

#ifdef __cplusplus
}
#endif
