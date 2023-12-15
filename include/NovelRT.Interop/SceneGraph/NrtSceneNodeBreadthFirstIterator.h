// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODEBREADTHFIRSTITERATOR_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODEBREADTHFIRSTITERATOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeBreadthFirstIterator_Create(NrtSceneNodeHandle node,
                                                       int32_t (*func)(NrtSceneNodeHandle, void*),
                                                       void* context,
                                                       NrtSceneNodeBreadthFirstIteratorHandle* outputIterator);
    NrtResult Nrt_SceneNodeBreadthFirstIterator_Increment(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    NrtResult Nrt_SceneNodeBreadthFirstIterator_PostFixIncrement(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    NrtBool Nrt_SceneNodeBreadthFirstIterator_IsEnd(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    int32_t Nrt_SceneNodeBreadthFirstIterator_RunFunction(NrtSceneNodeBreadthFirstIteratorHandle iterator);
    NrtBool Nrt_SceneNodeBreadthFirstIterator_IsEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                      NrtSceneNodeBreadthFirstIteratorHandle other);
    NrtBool Nrt_SceneNodeBreadthFirstIterator_IsNotEqual(NrtSceneNodeBreadthFirstIteratorHandle iterator,
                                                         NrtSceneNodeBreadthFirstIteratorHandle other);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENENODEBREADTHFIRSTITERATOR_H
