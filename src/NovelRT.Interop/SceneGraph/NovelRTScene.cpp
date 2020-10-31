// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stdint.h>
#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"
#include "NovelRT.Interop/SceneGraph/NovelRTScene.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

NovelRTScene NovelRT_Scene_create() {
  return reinterpret_cast<NovelRTScene>(new SceneGraph::Scene());
}

int32_t NovelRT_Scene_getNodes(NovelRTScene scene, NovelRTSceneNodeSet* outputSet) {
  if (scene == nullptr || outputSet == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet = new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
  *nodeSet = cppScene->getNodes();

  *outputSet = reinterpret_cast<NovelRTSceneNodeSet>(nodeSet);
  return NOVELRT_SUCCESS;
}


int32_t NovelRT_Scene_insert(NovelRTScene scene, NovelRTSceneNode nodeToInsert, int32_t* outputResult) {
  if (scene == nullptr || nodeToInsert == nullptr || outputResult == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  auto cppNode = reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this();

  *outputResult = cppScene->insert(cppNode);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Scene_remove(NovelRTScene scene, NovelRTSceneNode nodeToRemove, int32_t* outputResult) {
  if (scene == nullptr || nodeToRemove == nullptr || outputResult == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  auto cppNode = reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this();

  *outputResult = cppScene->remove(cppNode);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Scene_delete(NovelRTScene scene) {
  if (scene == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
  try {
    delete cppScene; //TODO: This can throw?????
  }
  catch(const std::exception& ex) {
    const char* message = ex.what();
    char* target = new char[strlen(message) + 1];
    strcpy(target, message);
    NovelRT_setErrMsgCustomInternal(target);
    return NOVELRT_FAILURE;
  }

  return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
