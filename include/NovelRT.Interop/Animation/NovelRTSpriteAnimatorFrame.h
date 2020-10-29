// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/NovelRTInteropUtils.h"

#ifndef NOVELRT_INTEROP_TIMING_TIMESTAMP_H
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#endif

#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
#include "NovelRT.Interop/Graphics/NovelRTGraphicsTypedefs.h"
#endif

#ifndef NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteAnimatorFrameHandle* NovelRTSpriteAnimatorFrame;

NovelRTSpriteAnimatorFrame NovelRT_SpriteAnimatorFrame_create();

int32_t NovelRT_SpriteAnimatorFrame_getTexture(NovelRTSpriteAnimatorFrame frame, NovelRTTexture* outputTexture);
int32_t NovelRT_SpriteAnimatorFrame_setTexture(NovelRTSpriteAnimatorFrame frame, NovelRTTexture texture);
int32_t NovelRT_SpriteAnimatorFrame_getDuration(NovelRTSpriteAnimatorFrame frame, NovelRTTimestamp* outputTimestamp);
int32_t NovelRT_SpriteAnimatorFrame_setDuration(NovelRTSpriteAnimatorFrame frame, NovelRTTimestamp timestamp);

int32_t NovelRT_SpriteAnimatorFrame_addFrameEnter(NovelRTSpriteAnimatorFrame frame, void(*func)());
int32_t NovelRT_SpriteAnimatorFrame_addFrameExit(NovelRTSpriteAnimatorFrame frame, void(*func)());

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H