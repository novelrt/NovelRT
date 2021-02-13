// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENE_H

#include "../NrtInteropUtils.h"
#include "NrtSceneGraphTypedefs.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtScene Nrt_Scene_create();
    NrtResult Nrt_Scene_getNodes(NrtScene scene, NrtSceneNodeSet* outputSet);
    NrtBool Nrt_Scene_insert(NrtScene scene, NrtSceneNode nodeToInsert);
    NrtBool Nrt_Scene_remove(NrtScene scene, NrtSceneNode nodeToRemove);
    NrtResult Nrt_Scene_delete(NrtScene scene);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENE_H
