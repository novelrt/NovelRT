// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H

#include <stddef.h>

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
#include "NrtSpriteAnimatorFrame.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorStateHandle* NrtSpriteAnimatorState;
typedef struct BoolFunctionVectorHandle* NrtSpriteAnimatorStateConditionFunctions;
typedef struct BoolFunctionHandle* NrtSpriteAnimatorStateBooleanFunction;   //Not known if this is needed yet.
typedef struct SpriteAnimatorFrameVectorHandle* NrtSpriteAnimatorFrameVector;

//SpriteAnimatorState
NrtSpriteAnimatorState Nrt_SpriteAnimatorState_create();
NrtResult Nrt_SpriteAnimatorState_insertNewState(NrtSpriteAnimatorState state, NrtSpriteAnimatorState stateTarget, NrtSpriteAnimatorStateConditionFunctions vector);
NrtResult Nrt_SpriteAnimatorState_removeStateAtIndex(NrtSpriteAnimatorState state, size_t index);
NrtResult Nrt_SpriteAnimatorState_getShouldLoop(NrtSpriteAnimatorState state, int32_t* outputLoop);
NrtResult Nrt_SpriteAnimatorState_setShouldLoop(NrtSpriteAnimatorState state, int32_t loop);
NrtResult Nrt_SpriteAnimatorState_getFrames(NrtSpriteAnimatorState state, NrtSpriteAnimatorFrameVector* outputFramess);
NrtResult Nrt_SpriteAnimatorState_setFrames(NrtSpriteAnimatorState state, NrtSpriteAnimatorFrameVector frames);
NrtResult Nrt_SpriteAnimatorState_tryFindValidTransition(NrtSpriteAnimatorState state, NrtSpriteAnimatorState* outputTransitionState);

//std::vector<SpriteAnimatorFrame>
NrtSpriteAnimatorFrameVector Nrt_SpriteAnimatorFrameVector_create();
NrtResult Nrt_SpriteAnimatorFrameVector_addFrame(NrtSpriteAnimatorFrameVector vector, NrtSpriteAnimatorFrame frame);
NrtResult Nrt_SpriteAnimatorFrameVector_getFrameAtIndex(NrtSpriteAnimatorFrameVector vector, int32_t index, NrtSpriteAnimatorFrame* outputFrame);
NrtResult Nrt_SpriteAnimatorFrameVector_removeFrameAtIndex(NrtSpriteAnimatorFrameVector vector, int32_t index);
NrtResult Nrt_SpriteAnimatorFrameVector_delete(NrtSpriteAnimatorFrameVector vector);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H