// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_ECS_AUDIO_AUDIOEMITTERCOMPONENT_H
#define NOVELRT_INTEROP_ECS_AUDIO_AUDIOEMITTERCOMPONENT_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void Nrt_AudioEmitterComponent_Update(NrtAudioEmitterComponent* lhs,
                                          const NrtAudioEmitterComponent* rhs,
                                          size_t size,
                                          void* context);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIO_AUDIOEMITTERCOMPONENT_H
