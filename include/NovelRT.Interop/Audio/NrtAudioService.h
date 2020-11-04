// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H
#define NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H

#include "../NrtInteropUtils.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AudioServiceHandle* NrtAudioService;
typedef struct IteratorHandle* NrtAudioServiceIterator;

NrtAudioService Nrt_AudioService_create();
int32_t Nrt_AudioService_destroy(NrtAudioService service);

int32_t Nrt_AudioService_initialiseAudio(NrtAudioService service, int32_t* output);
int32_t loadMusic(NrtAudioService service, char* input, NrtAudioServiceIterator* output);
    
int32_t Nrt_AudioService_setSoundVolume(NrtAudioService service, unsigned int source, float val);
int32_t Nrt_AudioService_setSoundPosition(NrtAudioService service, unsigned int source, float posX, float posY);
int32_t Nrt_AudioService_resumeMusic(NrtAudioService service);
int32_t Nrt_AudioService_playMusic(NrtAudioService service, NrtAudioServiceIterator handle, int loops);
int32_t Nrt_AudioService_pauseMusic(NrtAudioService service);
int32_t Nrt_AudioService_stopMusic(NrtAudioService service);
int32_t Nrt_AudioService_setMusicVolume(NrtAudioService service, float value);
int32_t Nrt_AudioService_checkSources(NrtAudioService service);
int32_t Nrt_AudioService_loadSound(NrtAudioService service, char* input, unsigned int* output);
int32_t Nrt_AudioService_unload(NrtAudioService service, unsigned int handle);
int32_t Nrt_AudioService_playSound(NrtAudioService service, unsigned int handle, int loops);
int32_t Nrt_AudioService_stopSound(NrtAudioService service, unsigned int handle);
int32_t Nrt_AudioService_tearDown(NrtAudioService service);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H