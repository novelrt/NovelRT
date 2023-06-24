// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_XAUDIO2_XAUDIO2ENGINE_H
#define NOVELRT_AUDIO_XAUDIO2_XAUDIO2ENGINE_H

#ifndef NOVELRT_AUDIO_XAUDIO2_H
#error NovelRT does not support including types explicitly by default. Please include Audio.XAudio2.h instead for the Audio namespace subset.
#endif



namespace NovelRT::Audio::XAudio2
{
    class XAudio2Engine final : public NovelRT::Audio::IAudioEngine
    {
        using BufferMap = std::map<std::string, std::pair<WAVEFORMATEXTENSIBLE, XAUDIO2_BUFFER>>;
        using VoiceMap = std::map<std::string, IXAudio2SourceVoice*>;
        using MetadataMap = std::map<std::string, NovelRT::ResourceManagement::AudioMetadata>;
    private:
        IXAudio2* _xAudio;
        IXAudio2MasteringVoice* _masterVoice;
        BufferMap _bufferMap;
        VoiceMap _voiceMap;
        MetadataMap _metaMap;
        NovelRT::LoggingService _logger;

        BufferMap::iterator CreateAudioBuffer(const std::string& soundName, const NovelRT::ResourceManagement::AudioMetadata& metadata);

    public:
        XAudio2Engine() noexcept;
        void Initialise();
        void Update();
        void TearDown();

        void LoadSound(const NovelRT::Audio::SoundDefinition& sound);
        void UnloadSound(const std::string& soundName);
        uint32_t PlaySound(const std::string& soundName, float volumeIndB);
        void StopSource(uint32_t sourceId);
        void PauseSource(uint32_t sourceId);
        void SetSourceVolume(uint32_t sourceId, float volumeIndB);
        bool IsPlaying(uint32_t sourceId);
    };
}

#endif // NOVELRT_AUDIO_XAUDIO2_XAUDIO2ENGINE_H
