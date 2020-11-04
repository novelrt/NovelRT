// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Animation/NrtAnimatorPlayState.h"

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
#include "NovelRT.Interop/Animation/NrtAnimatorState.h"
#endif

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#include "NovelRT.Interop/NrtNovelRunner.h"
#endif

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#include "NovelRT.Interop/Graphics/NrtGraphicsTypedefs.h"
#endif

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorHandle* NrtSpriteAnimator;

int32_t Nrt_SpriteAnimator_create(NrtNovelRunner runner, NrtImageRect rect, NrtSpriteAnimator* outputAnimator);
int32_t Nrt_SpriteAnimator_play(NrtSpriteAnimator animator);
int32_t Nrt_SpriteAnimator_pause(NrtSpriteAnimator animator);
int32_t Nrt_SpriteAnimator_stop(NrtSpriteAnimator animator);
int32_t Nrt_SpriteAnimator_getCurrentPlayState(NrtSpriteAnimator animator, NrtAnimatorPlayState* outputPlayState);
int32_t Nrt_SpriteAnimator_insertNewState(NrtSpriteAnimator animator, NrtSpriteAnimatorState state);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H