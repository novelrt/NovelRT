// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H
#define NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtAudioServiceHandle Nrt_AudioService_create();
    NrtResult Nrt_AudioService_destroy(NrtAudioServiceHandle service);

    NrtBool Nrt_AudioService_initialiseAudio(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_loadMusic(NrtAudioServiceHandle service, char* input, NrtAudioServiceIteratorHandle* output);

    NrtResult Nrt_AudioService_setSoundVolume(NrtAudioServiceHandle service, unsigned int source, float val);
    NrtResult Nrt_AudioService_setSoundPosition(NrtAudioServiceHandle service, unsigned int source, float posX, float posY);
    NrtResult Nrt_AudioService_resumeMusic(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_playMusic(NrtAudioServiceHandle service, NrtAudioServiceIteratorHandle handle, int32_t loops);
    NrtResult Nrt_AudioService_pauseMusic(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_stopMusic(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_setMusicVolume(NrtAudioServiceHandle service, float value);
    NrtResult Nrt_AudioService_checkSources(NrtAudioServiceHandle service);
    NrtResult Nrt_AudioService_loadSound(NrtAudioServiceHandle service, char* input, unsigned int* output);
    NrtResult Nrt_AudioService_unload(NrtAudioServiceHandle service, unsigned int handle);
    NrtResult Nrt_AudioService_playSound(NrtAudioServiceHandle service, unsigned int handle, int loops);
    NrtResult Nrt_AudioService_stopSound(NrtAudioServiceHandle service, unsigned int handle);
    NrtResult Nrt_AudioService_tearDown(NrtAudioServiceHandle service);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H
