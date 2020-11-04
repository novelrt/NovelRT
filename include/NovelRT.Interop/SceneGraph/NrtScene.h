// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceneHandle* NrtScene;

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NrtSceneNode;   //this worked? oh my gosssshhhhh //I CRI - Matt
typedef struct StdSet_SceneNode* NrtSceneNodeSet;
#endif

NrtScene Nrt_Scene_create();
int32_t Nrt_Scene_getNodes(NrtScene scene, NrtSceneNodeSet* outputSet);
int32_t Nrt_Scene_insert(NrtScene scene, NrtSceneNode nodeToInsert, int32_t* outputResult);
int32_t Nrt_Scene_remove(NrtScene scene, NrtSceneNode nodeToRemove, int32_t* outputResult);
int32_t Nrt_Scene_delete(NrtScene scene);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
