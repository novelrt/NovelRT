// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtTypedefs.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
using namespace NovelRT::Ecs;

extern "C"
{
#endif

    void Nrt_AudioEmitterComponent_Update(NrtAudioEmitterComponent* lhs,
                                          const NrtAudioEmitterComponent* rhs,
                                          size_t /*size*/,
                                          void* /*context*/)
    {
        *reinterpret_cast<Audio::AudioEmitterComponent*>(
            reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(lhs)->GetDataHandle()) +=
            *reinterpret_cast<const Audio::AudioEmitterComponent*>(
                reinterpret_cast<const SparseSetMemoryContainer::ByteIteratorView*>(rhs)->GetDataHandle());
    }

#ifdef __cplusplus
}
#endif
