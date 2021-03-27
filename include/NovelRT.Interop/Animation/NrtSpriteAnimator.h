// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SpriteAnimator_create(NrtNovelRunnerHandle runner, NrtImageRectHandle rect, NrtSpriteAnimatorHandle* outputAnimator);
    NrtResult Nrt_SpriteAnimator_play(NrtSpriteAnimatorHandle animator);
    NrtResult Nrt_SpriteAnimator_pause(NrtSpriteAnimatorHandle animator);
    NrtResult Nrt_SpriteAnimator_stop(NrtSpriteAnimatorHandle animator);
    NrtAnimatorPlayState Nrt_SpriteAnimator_getCurrentPlayState(NrtSpriteAnimatorHandle animator);
    NrtResult Nrt_SpriteAnimator_insertNewState(NrtSpriteAnimatorHandle animator, NrtSpriteAnimatorStateHandle state);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H
