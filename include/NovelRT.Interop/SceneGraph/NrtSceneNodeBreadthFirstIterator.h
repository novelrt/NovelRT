// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_BREADTHFIRSTITERATOR_H
#define NOVELRT_INTEROP_SCENEGRAPH_BREADTHFIRSTITERATOR_H

#include <stdint.h>
#include "../NrtInteropUtils.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneGraphTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

NrtResult Nrt_SceneNodeBreadthFirstIterator_create(NrtSceneNode node, int32_t(*func)(NrtSceneNode), NrtSceneNodeBreadthFirstIterator* outputIterator);
NrtResult Nrt_SceneNodeBreadthFirstIterator_increment(NrtSceneNodeBreadthFirstIterator iterator);
NrtResult Nrt_SceneNodeBreadthFirstIterator_postFixIncrement(NrtSceneNodeBreadthFirstIterator iterator);
NrtBool Nrt_SceneNodeBreadthFirstIterator_isEnd(NrtSceneNodeBreadthFirstIterator iterator);
int32_t Nrt_SceneNodeBreadthFirstIterator_runFunction(NrtSceneNodeBreadthFirstIterator iterator);
NrtBool Nrt_SceneNodeBreadthFirstIterator_isEqual(NrtSceneNodeBreadthFirstIterator iterator, NrtSceneNodeBreadthFirstIterator other);
NrtBool Nrt_SceneNodeBreadthFirstIterator_isNotEqual(NrtSceneNodeBreadthFirstIterator iterator, NrtSceneNodeBreadthFirstIterator other);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_BREADTHFIRSTITERATOR_H
