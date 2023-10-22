// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Audio/NrtAudioService.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;

extern "C"
{
#endif

    NrtAudioSystemHandle Nrt_AudioSystem_Create(NrtIResourceManagementPluginProviderHandle resourceManagementPlugin)
    {
        return reinterpret_cast<NrtAudioSystemHandle>(new Ecs::Audio::AudioSystem(
            reinterpret_cast<PluginManagement::IResourceManagementPluginProvider*>(resourceManagementPlugin)
                ->shared_from_this()));
    }

    NrtResult Nrt_AudioSystem_Destroy(NrtAudioSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::Audio::AudioSystem*>(system);
        sys->~AudioSystem();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioSystem_RegisterDefaultAudioComponents(NrtSystemSchedulerHandle system)
    {
        if (system == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::SystemScheduler*>(system);
        auto deleteState = Ecs::Audio::AudioEmitterComponent();
        sys->GetComponentCache().RegisterComponentType(deleteState, "NovelRT::Ecs::Audio::AudioEmitterComponent");
        sys->GetComponentCache().RegisterComponentType(
            Ecs::Audio::AudioEmitterStateComponent{Ecs::Audio::AudioEmitterState::Done},
            "NovelRT::Ecs::Audio::AudioEmitterStateComponent");
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioSystem_Update(NrtTimestamp delta, NrtCatalogueHandle catalogue, void* context)
    {

        if (context == nullptr || catalogue == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::Audio::AudioSystem*>(context);
        auto actualCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        sys->Update(Timing::Timestamp(delta), *actualCatalogue);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioSystem_CreateAudio(NrtAudioSystemHandle system,
                                          char* fileName,
                                          NrtBool isMusic,
                                          uint32_t* result)
    {
        if (system == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::Audio::AudioSystem*>(system);
        *result = sys->CreateAudio(fileName, isMusic);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioSystem_PushEmitterComponentUpdate(NrtSystemSchedulerHandle system,
                                                         NrtEntityId entity,
                                                         NrtAudioEmitterComponent emitter)
    {
        if (system == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::SystemScheduler*>(system);

        sys->GetComponentCache().GetComponentBuffer<Ecs::Audio::AudioEmitterComponent>().PushComponentUpdateInstruction(
            0, entity, *reinterpret_cast<Ecs::Audio::AudioEmitterComponent*>(&emitter));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_AudioSystem_PushEmitterStateComponentUpdate(NrtSystemSchedulerHandle system,
                                                              NrtEntityId entity,
                                                              NrtAudioEmitterStateComponent state)
    {
        if (system == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::SystemScheduler*>(system);

        sys->GetComponentCache()
            .GetComponentBuffer<Ecs::Audio::AudioEmitterStateComponent>()
            .PushComponentUpdateInstruction(0, entity,
                                            *reinterpret_cast<Ecs::Audio::AudioEmitterStateComponent*>(&state));

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
