// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_ANIMATION_ANIMATORPLAYSTATE_H
#define NOVELRT_INTEROP_ANIMATION_ANIMATORPLAYSTATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    Stopped = -1,
    Playing = 1,
    Paused = 0
} NovelRTAnimatorPlayState;

#ifdef __cplusplus
}
#endif


#endif //NOVELRT_INTEROP_ANIMATION_ANIMATORPLAYSTATE_H
