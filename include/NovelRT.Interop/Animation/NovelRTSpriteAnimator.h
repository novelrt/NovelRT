// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Animation/NovelRTAnimatorPlayState.h"

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORSTATE_H
#include "NovelRT.Interop/Animation/NovelRTSpriteAnimatorState.h"
#endif

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#endif

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#include "NovelRT.Interop/Graphics/NovelRTGraphicsTypedefs.h"
#endif

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorHandle* NovelRTSpriteAnimator;

int32_t NovelRT_SpriteAnimator_create(NovelRTNovelRunner runner, NovelRTImageRect rect, NovelRTSpriteAnimator* outputAnimator);
int32_t NovelRT_SpriteAnimator_play(NovelRTSpriteAnimator animator);
int32_t NovelRT_SpriteAnimator_pause(NovelRTSpriteAnimator animator);
int32_t NovelRT_SpriteAnimator_stop(NovelRTSpriteAnimator animator);
int32_t NovelRT_SpriteAnimator_getCurrentPlayState(NovelRTSpriteAnimator animator, NovelRTAnimatorPlayState* outputPlayState);
int32_t NovelRT_SpriteAnimator_insertNewState(NovelRTSpriteAnimator animator, NovelRTSpriteAnimatorState state);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H