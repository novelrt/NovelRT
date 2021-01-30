// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Audio/NrtAudioService.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.h>
#include <stdint.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtAudioService Nrt_AudioService_create()
    {
        return reinterpret_cast<NrtAudioService>(new Audio::AudioService()); // TODO: WTF??
    }

    NrtResult Nrt_AudioService_destroy(NrtAudioService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->~AudioService();
        return NRT_SUCCESS;
    }

    NrtBool Nrt_AudioService_initialiseAudio(NrtAudioService service)
    {
        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            return serv->initializeAudio() ? NRT_TRUE : NRT_FALSE;
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            Nrt_setErrMsgIsInitialisationFailureInternal();
            return NRT_FAILURE_INITIALISATION_FAILURE;
        }
    }

    NrtResult Nrt_AudioService_loadMusic(NrtAudioService service, char* input, NrtAudioServiceIterator* output)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        NovelRT::Audio::SoundBank::iterator out;
        try
        {
            out = serv->loadMusic(input);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        *output = reinterpret_cast<NrtAudioServiceIterator&>(out);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_setSoundVolume(NrtAudioService service, unsigned int source, float val)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->setSoundVolume(source, val);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_setSoundPosition(NrtAudioService service, unsigned int source, float posX, float posY)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->setSoundPosition(source, posX, posY);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_resumeMusic(NrtAudioService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->resumeMusic();
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_playMusic(NrtAudioService service, NrtAudioServiceIterator handle, int32_t loops)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->playMusic(reinterpret_cast<NovelRT::Audio::SoundBank::iterator&>(handle), loops);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_pauseMusic(NrtAudioService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->pauseMusic();
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_stopMusic(NrtAudioService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->stopMusic();
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_setMusicVolume(NrtAudioService service, float value)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->setMusicVolume(value);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_checkSources(NrtAudioService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->checkSources();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_loadSound(NrtAudioService service, char* input, unsigned int* output)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            *output = serv->loadSound(input);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_unload(NrtAudioService service, unsigned int handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->unload(handle);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_playSound(NrtAudioService service, unsigned int handle, int loops)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->playSound(handle, loops);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_stopSound(NrtAudioService service, unsigned int handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->stopSound(handle);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_tearDown(NrtAudioService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->tearDown();
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
