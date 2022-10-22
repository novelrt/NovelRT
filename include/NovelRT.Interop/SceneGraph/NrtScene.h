// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSceneHandle Nrt_Scene_create();
    NrtResult Nrt_Scene_getNodes(NrtSceneHandle scene, NrtSceneNodeSetHandle* outputSet);
    NrtBool Nrt_Scene_insert(NrtSceneHandle scene, NrtSceneNodeHandle nodeToInsert);
    NrtBool Nrt_Scene_remove(NrtSceneHandle scene, NrtSceneNodeHandle nodeToRemove);
    NrtResult Nrt_Scene_destroy(NrtSceneHandle scene);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
