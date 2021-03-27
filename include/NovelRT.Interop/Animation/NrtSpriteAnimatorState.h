// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSpriteAnimatorStateHandle Nrt_SpriteAnimatorState_create();
    NrtResult Nrt_SpriteAnimatorState_insertNewState(NrtSpriteAnimatorStateHandle state,
                                                     NrtSpriteAnimatorStateHandle stateTarget,
                                                     NrtSpriteAnimatorStateConditionFunctionsHandle vector);
    NrtResult Nrt_SpriteAnimatorState_removeStateAtIndex(NrtSpriteAnimatorStateHandle state, size_t index);
    int32_t Nrt_SpriteAnimatorState_getShouldLoop(NrtSpriteAnimatorStateHandle state);
    NrtResult Nrt_SpriteAnimatorState_setShouldLoop(NrtSpriteAnimatorStateHandle state, int32_t loop);
    NrtResult Nrt_SpriteAnimatorState_getFrames(NrtSpriteAnimatorStateHandle state,
                                                NrtSpriteAnimatorFrameVectorHandle* outputFramess);
    NrtResult Nrt_SpriteAnimatorState_setFrames(NrtSpriteAnimatorStateHandle state, NrtSpriteAnimatorFrameVectorHandle frames);
    NrtResult Nrt_SpriteAnimatorState_tryFindValidTransition(NrtSpriteAnimatorStateHandle state,
                                                             NrtSpriteAnimatorStateHandle* outputTransitionState);

    NrtSpriteAnimatorFrameVectorHandle Nrt_SpriteAnimatorFrameVector_create();
    NrtResult Nrt_SpriteAnimatorFrameVector_addFrame(NrtSpriteAnimatorFrameVectorHandle vector, NrtSpriteAnimatorFrameHandle frame);
    NrtResult Nrt_SpriteAnimatorFrameVector_getFrameAtIndex(NrtSpriteAnimatorFrameVectorHandle vector,
                                                            int32_t index,
                                                            NrtSpriteAnimatorFrameHandle* outputFrame);
    NrtResult Nrt_SpriteAnimatorFrameVector_removeFrameAtIndex(NrtSpriteAnimatorFrameVectorHandle vector, int32_t index);
    NrtResult Nrt_SpriteAnimatorFrameVector_delete(NrtSpriteAnimatorFrameVectorHandle vector);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
