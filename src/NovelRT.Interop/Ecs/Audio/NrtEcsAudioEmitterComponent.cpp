// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/Ecs/Audio/NrtEcsAudioTypedefs.h>

#ifdef __cplusplus
using namespace NovelRT::Ecs;

extern "C"
{
#endif

    void Nrt_Ecs_AudioEmitterComponent_update(NrtAudioEmitterComponent* lhs, NrtAudioEmitterComponent rhs, size_t /*size*/, void* /*context*/)
    {
        *reinterpret_cast<Audio::AudioEmitterComponent*>(lhs) += *reinterpret_cast<const Audio::AudioEmitterComponent*>(&rhs);
    }

#ifdef __cplusplus
}
#endif