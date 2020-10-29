// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <stddef.h>
#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
#include "NovelRT.Interop/Animation/NovelRTSpriteAnimatorFrame.h"
#endif

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorStateHandle* NovelRTSpriteAnimatorState;
typedef struct BoolFunctionVectorHandle* NovelRTSpriteAnimatorStateConditionFunctions;
typedef struct BoolFunctionHandle* NovelRTSpriteAnimatorStateBooleanFunction;   //Not known if this is needed yet.
typedef struct SpriteAnimatorFrameVectorHandle* NovelRTSpriteAnimatorFrameVector;

//SpriteAnimatorState
NovelRTSpriteAnimatorState NovelRT_SpriteAnimatorState_create();
int32_t NovelRT_SpriteAnimatorState_insertNewState(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorState stateTarget, NovelRTSpriteAnimatorStateConditionFunctions vector);
int32_t NovelRT_SpriteAnimatorState_removeStateAtIndex(NovelRTSpriteAnimatorState state, size_t index);
int32_t NovelRT_SpriteAnimatorState_getShouldLoop(NovelRTSpriteAnimatorState state, int32_t* outputLoop);
int32_t NovelRT_SpriteAnimatorState_setShouldLoop(NovelRTSpriteAnimatorState state, int32_t loop);
int32_t NovelRT_SpriteAnimatorState_getFrames(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorFrameVector* outputFramess);
int32_t NovelRT_SpriteAnimatorState_setFrames(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorFrameVector frames);
int32_t NovelRT_SpriteAnimatorState_tryFindValidTransition(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorState* outputTransitionState);

//std::vector<SpriteAnimatorFrame>
NovelRTSpriteAnimatorFrameVector NovelRT_SpriteAnimatorFrameVector_create();
int32_t NovelRT_SpriteAnimatorFrameVector_addFrame(NovelRTSpriteAnimatorFrameVector vector, NovelRTSpriteAnimatorFrame frame);
int32_t NovelRT_SpriteAnimatorFrameVector_getFrameAtIndex(NovelRTSpriteAnimatorFrameVector vector, int32_t index, NovelRTSpriteAnimatorFrame* outputFrame);
int32_t NovelRT_SpriteAnimatorFrameVector_removeFrameAtIndex(NovelRTSpriteAnimatorFrameVector vector, int32_t index);
int32_t NovelRT_SpriteAnimatorFrameVector_delete(NovelRTSpriteAnimatorFrameVector vector);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H