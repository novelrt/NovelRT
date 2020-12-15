// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_ANIMATIONTYPEDEFS_H
#define NOVELRT_INTEROP_ANIMATION_ANIMATIONTYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorFrameHandle* NrtSpriteAnimatorFrame;

typedef struct SpriteAnimatorStateHandle* NrtSpriteAnimatorState;
typedef struct BoolFunctionVectorHandle* NrtSpriteAnimatorStateConditionFunctions;
typedef struct SpriteAnimatorFrameVectorHandle* NrtSpriteAnimatorFrameVector;

typedef struct SpriteAnimatorHandle* NrtSpriteAnimator;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_ANIMATIONTYPEDEFS_H