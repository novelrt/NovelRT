// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_SCENENODEDEPTHFIRSTITERATOR_H
#define NOVELRT_INTEROP_SCENEGRAPH_SCENENODEDEPTHFIRSTITERATOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeDepthFirstIterator_create(NrtSceneNodeHandle node,
                                                     int32_t (*func)(NrtSceneNodeHandle, void*),
                                                     void* context,
                                                     NrtSceneNodeDepthFirstIteratorHandle* outputIterator);
    NrtResult Nrt_SceneNodeDepthFirstIterator_increment(NrtSceneNodeDepthFirstIteratorHandle iterator);
    NrtResult Nrt_SceneNodeDepthFirstIterator_postFixIncrement(NrtSceneNodeDepthFirstIteratorHandle iterator);
    NrtBool Nrt_SceneNodeDepthFirstIterator_isEnd(NrtSceneNodeDepthFirstIteratorHandle iterator);
    int32_t Nrt_SceneNodeDepthFirstIterator_runFunction(NrtSceneNodeDepthFirstIteratorHandle iterator);
    NrtBool Nrt_SceneNodeDepthFirstIterator_isEqual(NrtSceneNodeDepthFirstIteratorHandle iterator,
                                                    NrtSceneNodeDepthFirstIteratorHandle other);
    NrtBool Nrt_SceneNodeDepthFirstIterator_isNotEqual(NrtSceneNodeDepthFirstIteratorHandle iterator,
                                                       NrtSceneNodeDepthFirstIteratorHandle other);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_SCENENODEDEPTHFIRSTITERATOR_H
