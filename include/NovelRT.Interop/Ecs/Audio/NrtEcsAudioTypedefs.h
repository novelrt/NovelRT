// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_AUDIOTYPEDEFS_H
#define NOVELRT_INTEROP_ECS_AUDIOTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtEcsAudioSystem* NrtEcsAudioSystemHandle;

    typedef struct
    {
        uint32_t handle;
        NrtBool isMusic;
        int32_t numberOfLoops;
        float volume;
    } NrtAudioEmitterComponent;

    typedef enum
    {
        NRT_EMITTER_STATE_DONE = 0,
        NRT_EMITTER_STATE_TOPLAY = 1,
        NRT_EMITTER_STATE_PLAYING = 2,
        NRT_EMITTER_STATE_TOSTOP = 3,
        NRT_EMITTER_STATE_STOPPED = 4,
        NRT_EMITTER_STATE_TOPAUSE = 5,
        NRT_EMITTER_STATE_PAUSED = 6,
        NRT_EMITTER_STATE_TORESUME = 7,
    } NrtAudioEmitterStateKind;
    
    typedef int32_t NrtAudioEmitterState;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIOTYPEDEFS_H
