// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stdint.h>
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneNode.h"
#include "NovelRT.Interop/SceneGraph/NrtScene.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.h"

using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

NrtScene Nrt_Scene_create() {
  return reinterpret_cast<NrtScene>(new SceneGraph::Scene());
}

NrtResult Nrt_Scene_getNodes(NrtScene scene, NrtSceneNodeSet* outputSet) {
  if (scene == nullptr || outputSet == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet = new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
  *nodeSet = cppScene->getNodes();

  *outputSet = reinterpret_cast<NrtSceneNodeSet>(nodeSet);
  return NRT_SUCCESS;
}


NrtResult Nrt_Scene_insert(NrtScene scene, NrtSceneNode nodeToInsert, int32_t* outputResult) {
  if (scene == nullptr || nodeToInsert == nullptr || outputResult == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  auto cppNode = reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this();

  *outputResult = cppScene->insert(cppNode);
  return NRT_SUCCESS;
}

NrtResult Nrt_Scene_remove(NrtScene scene, NrtSceneNode nodeToRemove, int32_t* outputResult) {
  if (scene == nullptr || nodeToRemove == nullptr || outputResult == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  auto cppNode = reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this();

  *outputResult = cppScene->remove(cppNode);
  return NRT_SUCCESS;
}

NrtResult Nrt_Scene_delete(NrtScene scene) {
  if (scene == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  try {
    delete cppScene; //TODO: This can throw?????
  }
  catch(const std::exception& ex) {
    const char* message = ex.what();
    char* target = new char[strlen(message) + 1];
    strcpy_s(target, strlen(message) + 1, message);
    Nrt_setErrMsgCustomInternal(target);
    return NRT_FAILURE_UNKOWN;
  }

  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
