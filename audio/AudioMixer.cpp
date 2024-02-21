// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/AudioMixer.hpp>

//Conditional
#if defined(_WIN32)
#include <NovelRT/Audio/XAudio2/XAudio2AudioProvider.hpp>
#elif __APPLE__
#include <NovelRT/Audio/AVAudioEngine/AVAudioEngineAudioProvider.hpp>
#else
#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
#endif
namespace NovelRT::Audio
{
    void AudioMixer::Initialise()
    {
        _sourceContextCache = std::map<uint32_t, AudioSourceContext>();
#if defined(_WIN32)
        _audioProvider = std::make_unique<XAudio2::XAudio2AudioProvider>();
#elif defined(__APPLE__)
        _audioProvider = std::make_unique<AVAudioEngine::AVAudioEngineAudioProvider>();
#else
        _audioProvider = std::make_unique<OpenAL::OpenALAudioProvider>();
#endif
    }

    uint32_t AudioMixer::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, int32_t channelCount, int32_t originalSampleRate)
    {
        auto newContext = AudioSourceContext{};
        newContext.Channels = channelCount;
        newContext.SampleRate = originalSampleRate;
        uint32_t sourceId = _audioProvider->SubmitAudioBuffer(buffer, newContext);
        _sourceContextCache.emplace(sourceId, newContext);
        return sourceId;
    }

    AudioSourceState AudioMixer::GetSourceState(uint32_t id)
    {
        return _audioProvider->GetSourceState(id);
    }

    void AudioMixer::PlaySource(uint32_t id)
    {
        _audioProvider->PlaySource(id);
    }

    void AudioMixer::StopSource(uint32_t id)
    {
        _audioProvider->StopSource(id);
    }

    void AudioMixer::PauseSource(uint32_t id)
    {
        _audioProvider->PauseSource(id);
    }

    AudioSourceContext& AudioMixer::GetSourceContext(uint32_t id)
    {
        return _sourceContextCache.at(id);
    }

    void AudioMixer::SetSourceContext(uint32_t id, AudioSourceContext& context)
    {
        _sourceContextCache.erase(id);
        _sourceContextCache.emplace(id, context);
        _audioProvider->SetSourceProperties(id, context);
    }

    void AudioMixer::SetSourceVolume(uint32_t id, float volume)
    {
       auto& context = _sourceContextCache.at(id);
       context.Volume = volume;
       _audioProvider->SetSourceProperties(id, context);
    }

    void AudioMixer::SetSourcePitch(uint32_t id, float pitch)
    {
       auto& context = _sourceContextCache.at(id);
       context.Pitch = pitch;
       _audioProvider->SetSourceProperties(id, context);
    }

    void AudioMixer::SetSourceLoop(uint32_t id, bool isLooping)
    {
        auto& context = _sourceContextCache.at(id);
        context.Loop = isLooping;
        _audioProvider->SetSourceProperties(id, context);
    }

    void AudioMixer::TearDown()
    {
        _audioProvider.reset();
    }

    AudioMixer::~AudioMixer()
    {
        TearDown();
    }
}
