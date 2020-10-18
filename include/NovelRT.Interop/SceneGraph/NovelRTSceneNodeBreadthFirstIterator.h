// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_BREADTHFIRSTITERATOR_H
#define NOVELRT_INTEROP_SCENEGRAPH_BREADTHFIRSTITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreadthFirstIterator* NovelRTSceneNodeBreadthFirstIterator;
#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODE_H
typedef struct SceneNodeHandle* NovelRTSceneNode;   //this worked? oh my gosssshhhhh
#endif

int32_t NovelRT_SceneNodeBreadthFirstIterator_create(NovelRTSceneNode node, int32_t(*func)(NovelRTSceneNode), NovelRTSceneNodeBreadthFirstIterator* outputIterator, const char** errorMessage);
int32_t NovelRT_SceneNodeBreadthFirstIterator_increment(NovelRTSceneNodeBreadthFirstIterator iterator, const char** errorMessage);
int32_t NovelRT_SceneNodeBreadthFirstIterator_postFixIncrement(NovelRTSceneNodeBreadthFirstIterator iterator, const char** errorMessage);
int32_t NovelRT_SceneNodeBreadthFirstIterator_isEnd(NovelRTSceneNodeBreadthFirstIterator iterator, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNodeBreadthFirstIterator_runFunction(NovelRTSceneNodeBreadthFirstIterator iterator, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNodeBreadthFirstIterator_isEqual(NovelRTSceneNodeBreadthFirstIterator iterator, NovelRTSceneNodeBreadthFirstIterator other, int32_t* outputResult, const char** errorMessage);
int32_t NovelRT_SceneNodeBreadthFirstIterator_isNotEqual(NovelRTSceneNodeBreadthFirstIterator iterator, NovelRTSceneNodeBreadthFirstIterator other, int32_t* outputResult, const char** errorMessage);



#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_BREADTHFIRSTITERATOR_H
