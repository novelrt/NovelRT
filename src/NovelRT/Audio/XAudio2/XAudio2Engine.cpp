// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/XAudio2/Audio.XAudio2.h>



namespace NovelRT::Audio::XAudio2
{
    XAudio2Engine::XAudio2Engine() noexcept
    {
        _bufferMap = BufferMap();
        _voiceMap = VoiceMap();
        _metaMap = MetadataMap();
        _logger = NovelRT::LoggingService("XAUDIO");
    }

    void XAudio2Engine::Initialise()
    {
        _logger.logDebugLine("Initialising COM...");
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

        _logger.logDebugLine("Creating XAudio2 object...");
        
        if(FAILED(hr = XAudio2Create(&_xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR)))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            throw NovelRT::Exceptions::InitialisationFailureException(msg);
        }

        _logger.logDebugLine("Initialising XAudio2 mastering voice...");
        
        if(FAILED(hr = _xAudio->CreateMasteringVoice(&_masterVoice)))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            _logger.logErrorLine(msg);
            throw NovelRT::Exceptions::InitialisationFailureException(msg);
        }

        _logger.logDebugLine("Initialisation complete.");
    }

    void XAudio2Engine::Update()
    {

    }

    void XAudio2Engine::TearDown()
    {
        auto it = _voiceMap.begin();
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
            auto metaIt = _metaMap.emplace(sound.soundName, metadata);
            it = CreateAudioBuffer(sound.soundName, metaIt.first->second);
        }

        IXAudio2SourceVoice* voice;
        HRESULT hr;
        hr = _xAudio->CreateSourceVoice(&voice, reinterpret_cast<WAVEFORMATEX*>(&(it->second.first)));
        if(FAILED(hr))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            _logger.logWarning("Error when creating source voice:", msg);
            return;
        }

        hr = voice->SubmitSourceBuffer(&(it->second.second));
        if(FAILED(hr))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            _logger.logWarning("Error when submitting source buffer:", msg);
            return;
        }

        voice->SetVolume(XAudio2DecibelsToAmplitudeRatio(6.0));
        if(FAILED(hr))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            _logger.logWarning("Error when setting volume:", msg);
            return;
        }

        _voiceMap.emplace(sound.soundName, voice);
    }

    void XAudio2Engine::UnloadSound(const std::string& soundName)
    {
        unused(soundName);
    }

    uint32_t XAudio2Engine::PlaySound(const std::string& soundName, float volumeIndB)
    {
        auto voiceIt = _voiceMap.find(soundName);
        if(voiceIt == _voiceMap.end())
        {
            _logger.logWarning("Unable to find voice with loaded soundfile:", soundName);
            return 100;
        }

        HRESULT hr;

        unused(volumeIndB);

        hr = voiceIt->second->Start(0);
        if(FAILED(hr))
        {
            _com_error err(hr);
            std::string msg = err.ErrorMessage();
            _logger.logWarning("Error when starting playback:", msg);
            return 100;
        }

        _logger.logDebugLine("Playing sound:" + soundName);
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

    XAudio2Engine::BufferMap::iterator XAudio2Engine::CreateAudioBuffer(const std::string& soundName, const NovelRT::ResourceManagement::AudioMetadata& metadata)
    {
        WAVEFORMATEXTENSIBLE wfx = *(reinterpret_cast<const WAVEFORMATEXTENSIBLE*>(metadata.formatData.data()));
        XAUDIO2_BUFFER buffer = {0};        
        buffer.AudioBytes = metadata.audioDataSize;
        buffer.pAudioData = reinterpret_cast<const BYTE*>(metadata.audioData.data());
        buffer.Flags = XAUDIO2_END_OF_STREAM;   // Indicates all data for this stream was read already.

        auto result = _bufferMap.emplace(soundName, std::pair<WAVEFORMATEXTENSIBLE, XAUDIO2_BUFFER>(wfx, buffer));
        return result.first;
    }
}
