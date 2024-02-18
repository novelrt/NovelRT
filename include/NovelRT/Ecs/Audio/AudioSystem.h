// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H
#define NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H

#ifndef NOVELRT_ECS_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.Audio.h instead for the Ecs.Audio namespace subset.
#endif

namespace NovelRT::Ecs::Audio
{
    class AudioSystem : public Ecs::IEcsSystem
    {
    private:
        uint32_t _counter;
        LoggingService _logger;
        std::map<uint32_t, NovelRT::ResourceManagement::AudioMetadata> _soundCache;
        std::map<EntityId, std::tuple<NovelRT::Timing::Timestamp, float>> _fadeCache;
        std::shared_ptr<NovelRT::Audio::AudioMixer> _mixer;
        NovelRT::Timing::Timestamp _systemTime;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceManagerPluginProvider;

        // void ChangeAudioVolume(AudioEmitterComponent emitter, float desiredVolume);

    public:
        AudioSystem(std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagerPluginProvider);
        ~AudioSystem() noexcept;

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final;
        uint32_t RegisterSound(std::string fileName);
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOSYSTEM_H
