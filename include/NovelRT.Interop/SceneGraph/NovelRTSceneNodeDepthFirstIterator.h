// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H
#define NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DepthFirstIterator* NovelRTSceneNodeDepthFirstIterator;
#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NovelRTSceneNode;
#endif

int32_t NovelRT_SceneNodeDepthFirstIterator_create(NovelRTSceneNode node, int32_t(*func)(NovelRTSceneNode), NovelRTSceneNodeDepthFirstIterator* outputIterator, const char** errorMessage);
int32_t NovelRT_SceneNodeDepthFirstIterator_increment(NovelRTSceneNodeDepthFirstIterator iterator, const char** errorMessage);
int32_t NovelRT_SceneNodeDepthFirstIterator_postFixIncrement(NovelRTSceneNodeDepthFirstIterator iterator, const char** errorMessage);
int32_t NovelRT_SceneNodeDepthFirstIterator_isEnd(NovelRTSceneNodeDepthFirstIterator iterator, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNodeDepthFirstIterator_runFunction(NovelRTSceneNodeDepthFirstIterator iterator, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNodeDepthFirstIterator_isEqual(NovelRTSceneNodeDepthFirstIterator iterator, NovelRTSceneNodeDepthFirstIterator other, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNodeDepthFirstIterator_isNotEqual(NovelRTSceneNodeDepthFirstIterator iterator, NovelRTSceneNodeDepthFirstIterator other, int32_t* outputResult, const char** errorMessage);



#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H
