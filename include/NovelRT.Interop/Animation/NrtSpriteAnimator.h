// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../Graphics/NrtGraphicsTypedefs.h"
#include "../NrtNovelRunner.h"
#include "NrtAnimationTypedefs.h"
#include "NrtAnimatorPlayState.h"
#include "NrtSpriteAnimatorState.h"

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_SpriteAnimator_create(NrtNovelRunner runner, NrtImageRect rect, NrtSpriteAnimator* outputAnimator);
    NrtResult Nrt_SpriteAnimator_play(NrtSpriteAnimator animator);
    NrtResult Nrt_SpriteAnimator_pause(NrtSpriteAnimator animator);
    NrtResult Nrt_SpriteAnimator_stop(NrtSpriteAnimator animator);
    NrtAnimatorPlayState Nrt_SpriteAnimator_getCurrentPlayState(NrtSpriteAnimator animator);
    NrtResult Nrt_SpriteAnimator_insertNewState(NrtSpriteAnimator animator, NrtSpriteAnimatorState state);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATOR_H
