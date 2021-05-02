// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODEBREADTHFIRSTITERATOR_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODEBREADTHFIRSTITERATOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeBreadthFirstIterator_create(NrtSceneNodeHandle node,
                                                       int32_t (*func)(NrtSceneNodeHandle, void*),
                                                       void* context,
                                                       NrtSceneNodeBreadthFirstIteratorHandle* outputIterator);
    NrtResult Nrt_SceneNodeBreadthFirstIterator_increment(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    NrtResult Nrt_SceneNodeBreadthFirstIterator_postFixIncrement(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    NrtBool Nrt_SceneNodeBreadthFirstIterator_isEnd(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    int32_t Nrt_SceneNodeBreadthFirstIterator_runFunction(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    NrtBool Nrt_SceneNodeBreadthFirstIterator_isEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                      NrtSceneNodeBreadthFirstIteratorHandle other);
    NrtBool Nrt_SceneNodeBreadthFirstIterator_isNotEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                         NrtSceneNodeBreadthFirstIteratorHandle other);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENENODEBREADTHFIRSTITERATOR_H
