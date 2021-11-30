// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Audio/NrtAudioService.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;

extern "C"
{
#endif

    NrtAudioServiceHandle Nrt_AudioService_Create()
    {
        return reinterpret_cast<NrtAudioServiceHandle>(new Audio::AudioService());
    }

    NrtResult Nrt_AudioService_Destroy(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->~AudioService();
        return NRT_SUCCESS;
    }

    NrtBool Nrt_AudioService_InitialiseAudio(NrtAudioServiceHandle service)
    {
        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            return serv->InitializeAudio() ? NRT_TRUE : NRT_FALSE;
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            Nrt_setErrMsgIsInitialisationFailureInternal();
            return NRT_FAILURE_INITIALISATION_FAILURE;
        }
    }

    NrtResult Nrt_AudioService_LoadMusic(NrtAudioServiceHandle service,
                                         char* input,
                                         NrtAudioServiceIteratorHandle* output)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        NovelRT::Audio::SoundBank::iterator out;
        try
        {
            out = serv->LoadMusic(input);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        *output = reinterpret_cast<NrtAudioServiceIteratorHandle&>(out);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_SetSoundVolume(NrtAudioServiceHandle service, unsigned int source, float val)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->SetSoundVolume(source, val);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_SetSoundPosition(NrtAudioServiceHandle service,
                                                unsigned int source,
                                                float posX,
                                                float posY)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->SetSoundPosition(source, posX, posY);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_ResumeMusic(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->ResumeMusic();
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_PlayMusic(NrtAudioServiceHandle service,
                                         NrtAudioServiceIteratorHandle handle,
                                         int32_t loops)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->PlayMusic(reinterpret_cast<NovelRT::Audio::SoundBank::iterator&>(handle), loops);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_PauseMusic(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->PauseMusic();
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_StopMusic(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->StopMusic();
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_SetMusicVolume(NrtAudioServiceHandle service, float value)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->SetMusicVolume(value);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_CheckSources(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->CheckSources();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_LoadSound(NrtAudioServiceHandle service, char* input, unsigned int* output)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            *output = serv->LoadSound(input);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_Unload(NrtAudioServiceHandle service, unsigned int handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->Unload(handle);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_PlaySound(NrtAudioServiceHandle service, unsigned int handle, int loops)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        try
        {
            serv->PlaySound(handle, loops);
        }
        catch (const Exceptions::NotInitialisedException)
        {
            Nrt_setErrMsgIsNotInitialisedInternal();
            return NRT_FAILURE_NOT_INITIALISED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_StopSound(NrtAudioServiceHandle service, unsigned int handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->StopSound(handle);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioService_TearDown(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        serv->TearDown();
        return NRT_SUCCESS;
    }

    NrtBool Nrt_AudioService_IsMusicLoaded(NrtAudioServiceHandle service, NrtAudioServiceIteratorHandle handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        return serv->IsLoaded(reinterpret_cast<NovelRT::Audio::SoundBank::iterator&>(handle)) ? NRT_TRUE : NRT_FALSE;
    }

    NrtBool Nrt_AudioService_IsSoundLoaded(NrtAudioServiceHandle service, unsigned int handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        return serv->IsLoaded(handle) ? NRT_TRUE : NRT_FALSE;
    }

    NrtBool Nrt_AudioService_IsMusicPlaying(NrtAudioServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        return serv->IsMusicPlaying() ? NRT_TRUE : NRT_FALSE;
    }

    NrtBool Nrt_AudioService_IsSoundPlaying(NrtAudioServiceHandle service, unsigned int handle)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto serv = reinterpret_cast<Audio::AudioService*>(service);

        return serv->IsSoundPlaying(handle) ? NRT_TRUE : NRT_FALSE;
    }

    float Nrt_AudioService_GetMusicVolume(NrtAudioServiceHandle service)
    {
        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        return serv->GetMusicVolume();
    }

    float Nrt_AudioService_GetSoundVolume(NrtAudioServiceHandle service, unsigned int source)
    {
        auto serv = reinterpret_cast<Audio::AudioService*>(service);
        return serv->GetSoundVolume(source);
    }

#ifdef __cplusplus
}
#endif
