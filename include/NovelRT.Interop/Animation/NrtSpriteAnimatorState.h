// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H

#include <stddef.h>
#include "NovelRT.Interop/Animation/NrtAnimationTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

NrtSpriteAnimatorState Nrt_SpriteAnimatorState_create();
NrtResult Nrt_SpriteAnimatorState_insertNewState(NrtSpriteAnimatorState state, NrtSpriteAnimatorState stateTarget, NrtSpriteAnimatorStateConditionFunctions vector);
NrtResult Nrt_SpriteAnimatorState_removeStateAtIndex(NrtSpriteAnimatorState state, size_t index);
int32_t Nrt_SpriteAnimatorState_getShouldLoop(NrtSpriteAnimatorState state);
NrtResult Nrt_SpriteAnimatorState_setShouldLoop(NrtSpriteAnimatorState state, int32_t loop);
NrtResult Nrt_SpriteAnimatorState_getFrames(NrtSpriteAnimatorState state, NrtSpriteAnimatorFrameVector* outputFramess);
NrtResult Nrt_SpriteAnimatorState_setFrames(NrtSpriteAnimatorState state, NrtSpriteAnimatorFrameVector frames);
NrtResult Nrt_SpriteAnimatorState_tryFindValidTransition(NrtSpriteAnimatorState state, NrtSpriteAnimatorState* outputTransitionState);

NrtSpriteAnimatorFrameVector Nrt_SpriteAnimatorFrameVector_create();
NrtResult Nrt_SpriteAnimatorFrameVector_addFrame(NrtSpriteAnimatorFrameVector vector, NrtSpriteAnimatorFrame frame);
NrtResult Nrt_SpriteAnimatorFrameVector_getFrameAtIndex(NrtSpriteAnimatorFrameVector vector, int32_t index, NrtSpriteAnimatorFrame* outputFrame);
NrtResult Nrt_SpriteAnimatorFrameVector_removeFrameAtIndex(NrtSpriteAnimatorFrameVector vector, int32_t index);
NrtResult Nrt_SpriteAnimatorFrameVector_delete(NrtSpriteAnimatorFrameVector vector);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
