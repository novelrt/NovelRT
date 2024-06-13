// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_AUDIO_ECSAUDIOCOMPONENTS_H
#define NOVELRT_INTEROP_ECS_AUDIO_ECSAUDIOCOMPONENTS_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtAtom Nrt_Components_GetAudioEmitterComponentId();
    NrtAtom Nrt_Components_GetAudioEmitterStateComponentId();

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_AUDIO_ECSAUDIOCOMPONENTS_H
