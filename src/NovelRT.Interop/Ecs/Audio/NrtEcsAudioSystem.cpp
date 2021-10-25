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

    NrtEcsAudioSystemHandle Nrt_Ecs_AudioSystem_create()
    {
        return reinterpret_cast<NrtEcsAudioSystemHandle>(new Ecs::Audio::AudioSystem());
    }

    NrtResult Nrt_Ecs_AudioSystem_update(NrtEcsAudioSystemHandle system, NrtTimestamp delta, NrtCatalogueHandle catalogue)
    {
        if (system == nullptr || catalogue == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::Audio::AudioSystem*>(system);
        auto actualCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        sys->Update(Timing::Timestamp(delta), *actualCatalogue);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_Ecs_AudioSystem_createAudio(NrtEcsAudioSystemHandle system, char* fileName, NrtBool isMusic, uint32_t* result)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto sys = reinterpret_cast<Ecs::Audio::AudioSystem*>(system);
        *result = sys->CreateAudio(fileName, isMusic);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
