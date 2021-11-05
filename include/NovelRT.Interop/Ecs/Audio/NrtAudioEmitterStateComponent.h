// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H
#define NOVELRT_INTEROP_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H

#include "../NrtEcsTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void Nrt_AudioEmitterStateComponent_Update(void* lhs, const void* rhs, size_t size, void* context);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H
