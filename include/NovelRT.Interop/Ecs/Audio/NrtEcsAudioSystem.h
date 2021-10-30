// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_AUDIO_AUDIOSYSTEM_H
#define NOVELRT_INTEROP_ECS_AUDIO_AUDIOSYSTEM_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtEcsAudioSystemHandle Nrt_Ecs_AudioSystem_create();
    NrtResult Nrt_Ecs_AudioSystem_update(NrtEcsAudioSystemHandle system, NrtTimestamp delta, NrtCatalogueHandle catalogue);
    NrtResult Nrt_Ecs_AudioSystem_createAudio(NrtEcsAudioSystemHandle system, char* fileName, NrtBool isMusic, uint32_t* result);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIO_AUDIOSYSTEM_H
