// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H

#include "../Graphics/NrtGraphicsTypedefs.h"
#include "../NrtInteropUtils.h"
#include "../Timing/NrtTimestamp.h"
#include "NrtAnimationTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSpriteAnimatorFrame Nrt_SpriteAnimatorFrame_create();

    NrtResult Nrt_SpriteAnimatorFrame_getTexture(NrtSpriteAnimatorFrame frame, NrtTexture* outputTexture);
    NrtResult Nrt_SpriteAnimatorFrame_setTexture(NrtSpriteAnimatorFrame frame, NrtTexture texture);
    NrtTimestamp Nrt_SpriteAnimatorFrame_getDuration(NrtSpriteAnimatorFrame frame);
    NrtResult Nrt_SpriteAnimatorFrame_setDuration(NrtSpriteAnimatorFrame frame, NrtTimestamp timestamp);

    NrtResult Nrt_SpriteAnimatorFrame_addFrameEnter(NrtSpriteAnimatorFrame frame, void(*func)());
    NrtResult Nrt_SpriteAnimatorFrame_addFrameExit(NrtSpriteAnimatorFrame frame, void(*func)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
