// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_ANIMATIONTYPEDEFS_H
#define NOVELRT_INTEROP_ANIMATION_ANIMATIONTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtSpriteAnimator* NrtSpriteAnimatorHandle;
    typedef struct NrtSpriteAnimatorFrame* NrtSpriteAnimatorFrameHandle;
    typedef struct NrtSpriteAnimatorFrameVector* NrtSpriteAnimatorFrameVectorHandle;
    typedef struct NrtSpriteAnimatorState* NrtSpriteAnimatorStateHandle;
    typedef struct NrtSpriteAnimatorStateConditionFunctions* NrtSpriteAnimatorStateConditionFunctionsHandle;

    typedef enum
    {
        NRT_PLAY_STATE_STOPPED = 0,
        NRT_PLAY_STATE_PLAYING = 1,
        NRT_PLAY_STATE_PAUSED = 2
    } NrtAnimatorPlayStateKind;

    typedef int32_t NrtAnimatorPlayState;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_ANIMATIONTYPEDEFS_H
