// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H
#define NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H

namespace NovelRT::Ecs::Audio
{
    class AudioSystem : public Ecs::IEcsSystem
    {
    private:
        uint32_t _counter;
        std::map<uint32_t, std::vector<ALuint>::iterator> _musicCache;
        std::map<uint32_t, ALuint> _soundCache;
        std::shared_ptr<NovelRT::Audio::AudioService> _service;
        LoggingService _logger;

    public:
        AudioSystem();

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final;
        uint32_t CreateAudio(std::string fileName, bool isMusic);
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H
