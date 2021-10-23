// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H
#define NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H

namespace NovelRT::Audio
{
    class AudioSystem : public IEcsSystem
    {
    private:
        std::map<uint32_t, std::vector<ALuint>::iterator> _musicCache;
        std::map<uint32_t, ALuint> _soundCache;
    public:
        AudioSystem();

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final;
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H
