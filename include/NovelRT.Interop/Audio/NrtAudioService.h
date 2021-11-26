// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H
#define NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtAudioServiceHandle Nrt_AudioService_Create();
    NrtResult Nrt_AudioService_Destroy(NrtAudioServiceHandle service);

    NrtBool Nrt_AudioService_InitialiseAudio(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_LoadMusic(NrtAudioServiceHandle service,
                                         char* input,
                                         NrtAudioServiceIteratorHandle* output);

    NrtResult Nrt_AudioService_SetSoundVolume(NrtAudioServiceHandle service, unsigned int source, float val);
    NrtResult Nrt_AudioService_SetSoundPosition(NrtAudioServiceHandle service,
                                                unsigned int source,
                                                float posX,
                                                float posY);
    NrtResult Nrt_AudioService_ResumeMusic(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_PlayMusic(NrtAudioServiceHandle service,
                                         NrtAudioServiceIteratorHandle handle,
                                         int32_t loops);
    NrtResult Nrt_AudioService_PauseMusic(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_StopMusic(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_SetMusicVolume(NrtAudioServiceHandle service, float value);
    NrtResult Nrt_AudioService_CheckSources(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_LoadSound(NrtAudioServiceHandle service, char* input, unsigned int* output);
    NrtResult Nrt_AudioService_Unload(NrtAudioServiceHandle service, unsigned int handle);
    NrtResult Nrt_AudioService_PlaySound(NrtAudioServiceHandle service, unsigned int handle, int loops);
    NrtResult Nrt_AudioService_StopSound(NrtAudioServiceHandle service, unsigned int handle);
    NrtResult Nrt_AudioService_TearDown(NrtAudioServiceHandle service);
    NrtBool Nrt_AudioService_IsMusicLoaded(NrtAudioServiceHandle service, NrtAudioServiceIteratorHandle handle);
    NrtBool Nrt_AudioService_IsSoundLoaded(NrtAudioServiceHandle service, unsigned int handle);
    NrtBool Nrt_AudioService_IsMusicPlaying(NrtAudioServiceHandle service);
    NrtBool Nrt_AudioService_IsSoundPlaying(NrtAudioServiceHandle service, unsigned int handle);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H
