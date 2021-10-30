// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/Ecs/Audio/NrtEcsAudioTypedefs.h>

#ifdef __cplusplus
using namespace NovelRT::Ecs;

extern "C"
{
#endif

    void Nrt_Ecs_AudioEmitterStateComponent_update(NrtAudioEmitterStateComponent* lhs, NrtAudioEmitterStateComponent rhs, size_t /*size*/ size, void* context /*context*/)
    {
        *reinterpret_cast<Audio::AudioEmitterStateComponent*>(lhs) += *reinterpret_cast<const Audio::AudioEmitterStateComponent*>(&rhs);
    }

#ifdef __cplusplus
}
#endif