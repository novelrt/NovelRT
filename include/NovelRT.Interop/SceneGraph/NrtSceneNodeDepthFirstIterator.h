// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H
#define NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DepthFirstIterator* NrtSceneNodeDepthFirstIterator;
#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NrtSceneNode;
#endif

int32_t Nrt_SceneNodeDepthFirstIterator_create(NrtSceneNode node, int32_t(*func)(NrtSceneNode), NrtSceneNodeDepthFirstIterator* outputIterator);
int32_t Nrt_SceneNodeDepthFirstIterator_increment(NrtSceneNodeDepthFirstIterator iterator);
int32_t Nrt_SceneNodeDepthFirstIterator_postFixIncrement(NrtSceneNodeDepthFirstIterator iterator);
int32_t Nrt_SceneNodeDepthFirstIterator_isEnd(NrtSceneNodeDepthFirstIterator iterator, int32_t* outputResult);
int32_t Nrt_SceneNodeDepthFirstIterator_runFunction(NrtSceneNodeDepthFirstIterator iterator, int32_t* outputResult);
int32_t Nrt_SceneNodeDepthFirstIterator_isEqual(NrtSceneNodeDepthFirstIterator iterator, NrtSceneNodeDepthFirstIterator other, int32_t* outputResult);
int32_t Nrt_SceneNodeDepthFirstIterator_isNotEqual(NrtSceneNodeDepthFirstIterator iterator, NrtSceneNodeDepthFirstIterator other, int32_t* outputResult);



#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H
