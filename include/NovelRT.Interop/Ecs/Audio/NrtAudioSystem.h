// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_AUDIO_AUDIOSYSTEM_H
#define NOVELRT_INTEROP_ECS_AUDIO_AUDIOSYSTEM_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtAudioSystemHandle Nrt_AudioSystem_Create();
    NrtResult Nrt_AudioSystem_Destroy(NrtAudioSystemHandle service);
    NrtResult Nrt_AudioSystem_RegisterDefaultAudioComponents(NrtSystemSchedulerHandle system);
    NrtResult Nrt_AudioSystem_Update(NrtTimestamp delta, NrtCatalogueHandle catalogue, void* context);
    NrtResult Nrt_AudioSystem_CreateAudio(NrtAudioSystemHandle system,
                                          char* fileName,
                                          NrtBool isMusic,
                                          uint32_t* result);
    NrtResult Nrt_AudioSystem_PushEmitterComponentUpdate(NrtSystemSchedulerHandle system,
                                                         NrtEntityId entity,
                                                         NrtAudioEmitterComponent emitter);
    NrtResult Nrt_AudioSystem_PushEmitterStateComponentUpdate(NrtSystemSchedulerHandle system,
                                                              NrtEntityId entity,
                                                              NrtAudioEmitterStateComponent state);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIO_AUDIOSYSTEM_H
