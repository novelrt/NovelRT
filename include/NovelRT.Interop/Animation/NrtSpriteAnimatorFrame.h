// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSpriteAnimatorFrameHandle Nrt_SpriteAnimatorFrame_create();

    NrtResult Nrt_SpriteAnimatorFrame_getTexture(NrtSpriteAnimatorFrameHandle frame, NrtTextureHandle* outputTexture);
    NrtResult Nrt_SpriteAnimatorFrame_setTexture(NrtSpriteAnimatorFrameHandle frame, NrtTextureHandle texture);
    NrtTimestamp Nrt_SpriteAnimatorFrame_getDuration(NrtSpriteAnimatorFrameHandle frame);
    NrtResult Nrt_SpriteAnimatorFrame_setDuration(NrtSpriteAnimatorFrameHandle frame, NrtTimestamp timestamp);

    NrtResult Nrt_SpriteAnimatorFrame_addFrameEnter(NrtSpriteAnimatorFrameHandle frame, void (*func)());
    NrtResult Nrt_SpriteAnimatorFrame_addFrameExit(NrtSpriteAnimatorFrameHandle frame, void (*func)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
