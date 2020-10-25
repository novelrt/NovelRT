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

int32_t NovelRT_SpriteAnimatorFrame_getTexture(NovelRTSpriteAnimatorFrame frame, NovelRTTexture* outputTexture, const char** errorMessage);
int32_t NovelRT_SpriteAnimatorFrame_setTexture(NovelRTSpriteAnimatorFrame frame, NovelRTTexture texture, const char** errorMessage);
int32_t NovelRT_SpriteAnimatorFrame_getDuration(NovelRTSpriteAnimatorFrame frame, NovelRTTimestamp* outputTimestamp, const char** errorMessage);
int32_t NovelRT_SpriteAnimatorFrame_setDuration(NovelRTSpriteAnimatorFrame frame, NovelRTTimestamp timestamp, const char** errorMessage);

int32_t NovelRT_SpriteAnimatorFrame_addFrameEnter(NovelRTSpriteAnimatorFrame frame, void(*func)(), const char** errorMessage);
int32_t NovelRT_SpriteAnimatorFrame_addFrameExit(NovelRTSpriteAnimatorFrame frame, void(*func)(), const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ANIMATION_SPRITEANIMATORFRAME_H