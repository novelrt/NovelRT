// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_AUDIOTYPEDEFS_H
#define NOVELRT_INTEROP_ECS_AUDIOTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtAudioSystem* NrtAudioSystemHandle;

    typedef struct
    {
        uint32_t handle;
        int32_t isMusic;
        int32_t numberOfLoops;
        float volume;
    } NrtAudioEmitterComponent;

    typedef enum
    {
        NRT_EMITTER_STATE_DONE = 0,
        NRT_EMITTER_STATE_TO_PLAY = 1,
        NRT_EMITTER_STATE_PLAYING = 2,
        NRT_EMITTER_STATE_TO_STOP = 3,
        NRT_EMITTER_STATE_STOPPED = 4,
        NRT_EMITTER_STATE_TO_PAUSE = 5,
        NRT_EMITTER_STATE_PAUSED = 6,
        NRT_EMITTER_STATE_TO_RESUME = 7,
        NRT_EMITTER_STATE_TO_FADE_IN = 8,
        NRT_EMITTER_STATE_FADING_IN = 9,
        NRT_EMITTER_STATE_TO_FADE_OUT = 10,
        NRT_EMITTER_STATE_FADING_OUT = 11
    } NrtAudioEmitterStateKind;

    typedef int32_t NrtAudioEmitterState;

    typedef struct
    {
        NrtAudioEmitterState state;
    } NrtAudioEmitterStateComponent;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIOTYPEDEFS_H
