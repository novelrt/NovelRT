// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H
#define NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H

#include "../NrtInteropUtils.h"
#include "NrtSceneGraphTypedefs.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SceneNodeDepthFirstIterator_create(NrtSceneNode node, int32_t (*func)(NrtSceneNode),
                                                     NrtSceneNodeDepthFirstIterator* outputIterator);
    NrtResult Nrt_SceneNodeDepthFirstIterator_increment(NrtSceneNodeDepthFirstIterator iterator);
    NrtResult Nrt_SceneNodeDepthFirstIterator_postFixIncrement(NrtSceneNodeDepthFirstIterator iterator);
    NrtBool Nrt_SceneNodeDepthFirstIterator_isEnd(NrtSceneNodeDepthFirstIterator iterator);
    int32_t Nrt_SceneNodeDepthFirstIterator_runFunction(NrtSceneNodeDepthFirstIterator iterator);
    NrtBool Nrt_SceneNodeDepthFirstIterator_isEqual(NrtSceneNodeDepthFirstIterator iterator,
                                                    NrtSceneNodeDepthFirstIterator other);
    NrtBool Nrt_SceneNodeDepthFirstIterator_isNotEqual(NrtSceneNodeDepthFirstIterator iterator,
                                                       NrtSceneNodeDepthFirstIterator other);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_DepthFirstIterator_H
