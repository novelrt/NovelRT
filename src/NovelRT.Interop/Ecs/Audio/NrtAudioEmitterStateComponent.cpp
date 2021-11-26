// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT.Interop/Ecs/Audio/NrtEcsAudioTypedefs.h>

#ifdef __cplusplus
using namespace NovelRT::Ecs;

extern "C"
{
#endif

    void Nrt_AudioEmitterStateComponent_Update(NrtAudioEmitterStateComponent* lhs, const NrtAudioEmitterStateComponent* rhs, size_t /*size*/, void* /*context*/)
    {
        *reinterpret_cast<Audio::AudioEmitterStateComponent*>(reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(lhs)->GetDataHandle()) += *reinterpret_cast<const Audio::AudioEmitterStateComponent*>(reinterpret_cast<const SparseSetMemoryContainer::ByteIteratorView*>(rhs)->GetDataHandle());
    }

#ifdef __cplusplus
}
#endif
