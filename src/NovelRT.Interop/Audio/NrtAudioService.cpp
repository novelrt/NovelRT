// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Audio/NrtAudioService.h"
#include <NovelRT.h>
#include <stdint.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtAudioService Nrt_AudioService_create() {
    return reinterpret_cast<NrtAudioService>(new Audio::AudioService()); //TODO: WTF??
}

NrtResult Nrt_AudioService_destroy(NrtAudioService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->~AudioService();
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_initialiseAudio(NrtAudioService service, int32_t* output) {
    if (service == NULL) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    *output = serv->initializeAudio()? NRT_TRUE : NRT_FALSE;
    return NRT_SUCCESS;
}


int32_t loadMusic(NrtAudioService service, char* input, NrtAudioServiceIterator* output) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    auto out = serv->loadMusic(input);
    *output = reinterpret_cast<NrtAudioServiceIterator&>(out);
    return NRT_SUCCESS;
}
    
NrtResult Nrt_AudioService_setSoundVolume(NrtAudioService service, unsigned int source, float val) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->setSoundVolume(source, val);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_setSoundPosition(NrtAudioService service, unsigned int source, float posX, float posY) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->setSoundPosition(source, posX, posY);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_resumeMusic(NrtAudioService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->resumeMusic();
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_playMusic(NrtAudioService service, NrtAudioServiceIterator handle, int loops) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->playMusic(reinterpret_cast<NovelRT::Audio::SoundBank::iterator&>(handle), loops);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_pauseMusic(NrtAudioService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->pauseMusic();
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_stopMusic(NrtAudioService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->stopMusic();
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_setMusicVolume(NrtAudioService service, float value) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->setMusicVolume(value);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_checkSources(NrtAudioService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->checkSources();
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_loadSound(NrtAudioService service, char* input, unsigned int* output) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    *output = serv->loadSound(input);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_unload(NrtAudioService service, unsigned int handle) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->unload(handle);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_playSound(NrtAudioService service, unsigned int handle, int loops) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->playSound(handle, loops);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_stopSound(NrtAudioService service, unsigned int handle) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->stopSound(handle);
    return NRT_SUCCESS;
}

NrtResult Nrt_AudioService_tearDown(NrtAudioService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto serv = reinterpret_cast<Audio::AudioService*>(service);
    serv->tearDown();
    return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif

