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
int32_t NovelRT_AudioService_destroy(NovelRTAudioService service, const char** errorMessage);

int32_t NovelRT_AudioService_initialiseAudio(NovelRTAudioService service, int32_t* output, const char** errorMessage);
int32_t loadMusic(NovelRTAudioService service, char* input, NovelRTAudioServiceIterator* output, const char** errorMessage);
    
int32_t NovelRT_AudioService_setSoundVolume(NovelRTAudioService service, unsigned int source, float val, const char** errorMessage);
int32_t NovelRT_AudioService_setSoundPosition(NovelRTAudioService service, unsigned int source, float posX, float posY, const char** errorMessage);
int32_t NovelRT_AudioService_resumeMusic(NovelRTAudioService service, const char** errorMessage);
int32_t NovelRT_AudioService_playMusic(NovelRTAudioService service, NovelRTAudioServiceIterator handle, int loops, const char** errorMessage);
int32_t NovelRT_AudioService_pauseMusic(NovelRTAudioService service, const char** errorMessage);
int32_t NovelRT_AudioService_stopMusic(NovelRTAudioService service, const char** errorMessage);
int32_t NovelRT_AudioService_setMusicVolume(NovelRTAudioService service, float value, const char** errorMessage);
int32_t NovelRT_AudioService_checkSources(NovelRTAudioService service, const char** errorMessage);
int32_t NovelRT_AudioService_loadSound(NovelRTAudioService service, char* input, unsigned int* output, const char** errorMessage);
int32_t NovelRT_AudioService_unload(NovelRTAudioService service, unsigned int handle, const char** errorMessage);
int32_t NovelRT_AudioService_playSound(NovelRTAudioService service, unsigned int handle, int loops, const char** errorMessage);
int32_t NovelRT_AudioService_stopSound(NovelRTAudioService service, unsigned int handle, const char** errorMessage);
int32_t NovelRT_AudioService_tearDown(NovelRTAudioService service, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_AUDIO_AUDIOSERVICE_H