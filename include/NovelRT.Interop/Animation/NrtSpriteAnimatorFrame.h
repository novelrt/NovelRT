// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H

//TODO: Fix these includes. Idk why we have repeated guards here.
#include "../NrtInteropUtils.h" 

#ifndef NOVELRT_INTEROP_TIMING_TIMESTAMP_H
#include "../Timing/NrtTimestamp.h"
#endif

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#include "../Graphics/NrtGraphicsTypedefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorFrameHandle* NrtSpriteAnimatorFrame;

NrtSpriteAnimatorFrame Nrt_SpriteAnimatorFrame_create();

int32_t Nrt_SpriteAnimatorFrame_getTexture(NrtSpriteAnimatorFrame frame, NrtTexture* outputTexture);
int32_t Nrt_SpriteAnimatorFrame_setTexture(NrtSpriteAnimatorFrame frame, NrtTexture texture);
int32_t Nrt_SpriteAnimatorFrame_getDuration(NrtSpriteAnimatorFrame frame, NrtTimestamp* outputTimestamp);
int32_t Nrt_SpriteAnimatorFrame_setDuration(NrtSpriteAnimatorFrame frame, NrtTimestamp timestamp);

int32_t Nrt_SpriteAnimatorFrame_addFrameEnter(NrtSpriteAnimatorFrame frame, void(*func)());
int32_t Nrt_SpriteAnimatorFrame_addFrameExit(NrtSpriteAnimatorFrame frame, void(*func)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H