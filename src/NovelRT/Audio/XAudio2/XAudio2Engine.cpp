// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/XAudio2/Audio.XAudio2.h>

namespace NovelRT::Audio::XAudio2
{
    XAudio2Engine::XAudio2Engine() noexcept
    {
        _bufferMap = BufferMap();
        _voiceMap = VoiceMap();
    }

    void XAudio2Engine::Initialise()
    {
        //Note - We will want to revisit this when it is time for UWP support.
        HRESULT hr;
        hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        if(FAILED(hr))
        {
            //Note - Need to add support for wide-char at a later date.
            //(If/when exceptions support unicode.)
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InitialisationFailureException(msg);
        }

        _xAudio = std::shared_ptr<IXAudio2>(nullptr);
        IXAudio2* xA = _xAudio.get();
        if(FAILED(hr = XAudio2Create(&xA, 0, XAUDIO2_DEFAULT_PROCESSOR)))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InitialisationFailureException(msg);
        }

        _masterVoice = std::shared_ptr<IXAudio2MasteringVoice>(nullptr);
        IXAudio2MasteringVoice* mV = _masterVoice.get();
        if(FAILED(hr = _xAudio->CreateMasteringVoice(&mV)))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InitialisationFailureException(msg);
        }

    }

    void XAudio2Engine::Update()
    {

    }

    void XAudio2Engine::TearDown()
    {

    }

    void XAudio2Engine::LoadSound(const NovelRT::Audio::SoundDefinition& sound)
    {
        //Check if sound exists in voice map
        auto voiceIt = _voiceMap.find(sound.soundName);
        if(voiceIt != _voiceMap.end())
        {
            return;
        }

        //Voice does not exist, check if it is loaded already.
        auto it = _bufferMap.find(sound.soundName);
        if(it == _bufferMap.end())
        {
            auto metadata = NovelRT::ResourceManagement::Desktop::DesktopResourceLoader::LoadAudioFrameData(sound.soundName);
            it = CreateAudioBuffer(sound.soundName, metadata);
        }

        auto sharedVoice = std::shared_ptr<IXAudio2SourceVoice>(nullptr);
        IXAudio2SourceVoice* voice = sharedVoice.get();
        HRESULT hr;
        hr = _xAudio->CreateSourceVoice(&voice, reinterpret_cast<WAVEFORMATEX*>(&(it->second.first)));
        if(FAILED(hr))
        {
            //TODO: make this log, but not throw its toys out the pram
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InvalidOperationException(msg);
        }

        hr = voice->SubmitSourceBuffer(&(it->second.second));
        if(FAILED(hr))
        {
            //TODO: make this log, but not throw its toys out the pram
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InvalidOperationException(msg);
        }

        voice->SetVolume(XAudio2DecibelsToAmplitudeRatio(sound.defaultVolumeIndB));
        if(FAILED(hr))
        {
            //TODO: make this log, but not throw its toys out the pram
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InvalidOperationException(msg);
        }

        _voiceMap.emplace(sound.soundName, sharedVoice);
    }

    void XAudio2Engine::UnloadSound(const std::string& soundName)
    {
        unused(soundName);
    }

    uint32_t XAudio2Engine::PlaySound(const std::string& soundName, float volumeIndB)
    {
        unused(soundName);
        unused(volumeIndB);
        return 0;
    }

    void XAudio2Engine::StopSource(uint32_t sourceId)
    {
        unused(sourceId);
    }

    void XAudio2Engine::PauseSource(uint32_t sourceId)
    {
        unused(sourceId);
    }

    void XAudio2Engine::SetSourceVolume(uint32_t sourceId, float volumeIndB)
    {
        unused(sourceId);
        unused(volumeIndB);
    }

    bool XAudio2Engine::IsPlaying(uint32_t sourceId)
    {
        unused(sourceId);
        return false;
    }

    XAudio2Engine::BufferMap::iterator XAudio2Engine::CreateAudioBuffer(const std::string& soundName, NovelRT::ResourceManagement::AudioMetadata metadata)
    {
        WAVEFORMATEXTENSIBLE wfx = *(reinterpret_cast<WAVEFORMATEXTENSIBLE*>(metadata.formatData.data()));
        XAUDIO2_BUFFER buffer = {0};
        buffer.AudioBytes = metadata.audioDataSize;
        buffer.pAudioData = reinterpret_cast<BYTE*>(metadata.audioData.data());
        buffer.Flags = XAUDIO2_END_OF_STREAM;   // Indicates all data for this stream was read already.

        auto result = _bufferMap.emplace(soundName, std::pair<WAVEFORMATEXTENSIBLE, XAUDIO2_BUFFER>(wfx, buffer));
        return result.first;
    }
}
