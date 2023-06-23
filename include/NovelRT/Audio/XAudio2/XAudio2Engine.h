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
        typedef std::map<std::string, std::pair<WAVEFORMATEXTENSIBLE, XAUDIO2_BUFFER>> BufferMap;
        typedef std::map<std::string, std::shared_ptr<IXAudio2SourceVoice>> VoiceMap;

    private:
        std::shared_ptr<IXAudio2> _xAudio;
        std::shared_ptr<IXAudio2MasteringVoice> _masterVoice;
        BufferMap _bufferMap;
        VoiceMap _voiceMap;

        BufferMap::iterator CreateAudioBuffer(const std::string& soundName, NovelRT::ResourceManagement::AudioMetadata metadata);

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
