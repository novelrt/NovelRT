// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceneHandle* NovelRTScene;

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NovelRTSceneNode;   //this worked? oh my gosssshhhhh
typedef struct StdSet_SceneNode* NovelRTSceneNodeSet;
#endif

NovelRTScene NovelRT_Scene_create();
int32_t NovelRT_Scene_getNodes(NovelRTScene scene, NovelRTSceneNodeSet* outputSet);
int32_t NovelRT_Scene_insert(NovelRTScene scene, NovelRTSceneNode nodeToInsert, int32_t* outputResult);
int32_t NovelRT_Scene_remove(NovelRTScene scene, NovelRTSceneNode nodeToRemove, int32_t* outputResult);
int32_t NovelRT_Scene_delete(NovelRTScene scene);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
