// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <stdint.h>

#ifndef NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H
#define NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct AudioServiceHandle* NovelRTAudioService;
typedef struct IteratorHandle* NovelRTAudioServiceIterator;

NovelRTAudioService NovelRT_AudioService_create();
int32_t NovelRT_AudioService_destroy(NovelRTAudioService service);

int32_t NovelRT_AudioService_initialiseAudio(NovelRTAudioService service, int32_t* output);
int32_t loadMusic(NovelRTAudioService service, char* input, NovelRTAudioServiceIterator* output);
    
int32_t NovelRT_AudioService_setSoundVolume(NovelRTAudioService service, unsigned int source, float val);
int32_t NovelRT_AudioService_setSoundPosition(NovelRTAudioService service, unsigned int source, float posX, float posY);
int32_t NovelRT_AudioService_resumeMusic(NovelRTAudioService service);
int32_t NovelRT_AudioService_playMusic(NovelRTAudioService service, NovelRTAudioServiceIterator handle, int loops);
int32_t NovelRT_AudioService_pauseMusic(NovelRTAudioService service);
int32_t NovelRT_AudioService_stopMusic(NovelRTAudioService service);
int32_t NovelRT_AudioService_setMusicVolume(NovelRTAudioService service, float value);
int32_t NovelRT_AudioService_checkSources(NovelRTAudioService service);
int32_t NovelRT_AudioService_loadSound(NovelRTAudioService service, char* input, unsigned int* output);
int32_t NovelRT_AudioService_unload(NovelRTAudioService service, unsigned int handle);
int32_t NovelRT_AudioService_playSound(NovelRTAudioService service, unsigned int handle, int loops);
int32_t NovelRT_AudioService_stopSound(NovelRTAudioService service, unsigned int handle);
int32_t NovelRT_AudioService_tearDown(NovelRTAudioService service);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H