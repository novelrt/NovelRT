// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Audio/NrtEcsAudioComponents.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Audio;

NrtAtom Nrt_Components_GetAudioEmitterComponentId()
{
    return GetComponentTypeId<AudioEmitterComponent>();
}

NrtAtom Nrt_Components_GetAudioEmitterStateComponentId()
{
    return GetComponentTypeId<AudioEmitterStateComponent>();
}