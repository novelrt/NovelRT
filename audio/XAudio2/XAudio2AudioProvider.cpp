// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/XAudio2/XAudio2AudioProvider.hpp>
#include <NovelRT/Exceptions/Exceptions.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace NovelRT::Audio::XAudio2
{

    XAudio2AudioProvider::XAudio2AudioProvider():
    _device(nullptr),
    _masterVoice(nullptr),
    _sources(std::map<uint32_t, IXAudio2SourceVoice*>()),
    _sourceCounter(0),
    _logger(spdlog::stdout_color_mt("XAudio2")),
    _buffers(std::map<uint32_t, XAUDIO2_BUFFER>()),
    _bufferCounter(0)
    {
        //Logger init
        _logger->set_level(spdlog::level::debug);

        //Device and Context Init
        _hr = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
        if (FAILED(_hr))
        {
            throw new Exceptions::InitialisationFailureException("Failed to initialise COM!", _hr);
        }

        if (FAILED(_hr = XAudio2Create( &_device, 0, XAUDIO2_DEFAULT_PROCESSOR)))
        {
            throw new Exceptions::InitialisationFailureException("Failed to create an instance of the XAudio2 engine!", _hr);
        }

        if (FAILED(_hr = _device->CreateMasteringVoice(&_masterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE)))
        {
            throw new Exceptions::InitialisationFailureException("Failed to create an output voice!", _hr);
        }

        XAUDIO2_DEBUG_CONFIGURATION debug{};
        debug.TraceMask = XAUDIO2_LOG_ERRORS;
        _device->SetDebugConfiguration(&debug);

        _logger->info("XAudio2 initialised.");
    }

    XAudio2AudioProvider::~XAudio2AudioProvider()
    {
        Dispose();
    }

    void XAudio2AudioProvider::Dispose()
    {
        for(auto [id, source] : _sources)
        {
            source->FlushSourceBuffers();
            source->DestroyVoice();
        }
        _sources.clear();
        _buffers.clear();
        _masterVoice->DestroyVoice();
        _device->StopEngine();
    }

    uint32_t XAudio2AudioProvider::OpenSource(AudioSourceContext& context)
    {
        uint32_t nextSource = ++_sourceCounter;
        WAVEFORMATEX waveFormatContainer{};
        waveFormatContainer.wFormatTag = WAVE_FORMAT_PCM;
        waveFormatContainer.nChannels = 2;
        waveFormatContainer.nSamplesPerSec = static_cast<long>(context.SampleRate);
        waveFormatContainer.nAvgBytesPerSec = static_cast<long>(context.SampleRate / 0.25);
        waveFormatContainer.nBlockAlign = 4;
        waveFormatContainer.wBitsPerSample = 16;
        waveFormatContainer.cbSize = 0;


        IXAudio2SourceVoice* newVoice;
        if(FAILED(_hr = _device->CreateSourceVoice(&newVoice, &waveFormatContainer)))
        {
            _logger->error("Could not create source voice - Code: {hr}", _hr);
        }

        _sources.emplace(nextSource, newVoice);
        return nextSource;
    }

    void XAudio2AudioProvider::PlaySource(uint32_t sourceId)
    {
        if(FAILED(_hr = _sources.at(sourceId)->Start(0)))
        {
            _logger->error("Error when attempting to play source {id} - Code: {hr}", sourceId, _hr);
        }
    }

    void XAudio2AudioProvider::StopSource(uint32_t sourceId)
    {
        if(FAILED(_hr = _sources.at(sourceId)->Stop(0)))
        {
            _logger->error("Error when stopping source {id} - Code: {hr}", sourceId, _hr);
        }
    }

    void XAudio2AudioProvider::PauseSource(uint32_t sourceId)
    {
        PlaySource(sourceId);
    }

    uint32_t XAudio2AudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context)
    {
        uint32_t nextBuffer = ++_bufferCounter;
        XAUDIO2_BUFFER xABuffer =
        {
            XAUDIO2_END_OF_STREAM,          // Flags
            static_cast<uint32_t>(buffer.size()*sizeof(int16_t)),  // AudioBytes
            static_cast<byte*>(new byte[buffer.size()*sizeof(int16_t)])
        };

        std::memcpy((void*)(xABuffer.pAudioData),
             reinterpret_cast<void*>(buffer.data()), buffer.size()*sizeof(int16_t));
        if(context.Loop)
        {
            xABuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
        }

        _buffers.emplace(nextBuffer, xABuffer);
        uint32_t sourceId = OpenSource(context);

        if(FAILED(_hr = _sources.at(sourceId)->SubmitSourceBuffer(&xABuffer)))
        {
            _logger->error("Failed to submit buffer to source {sourceId} - Code: {hr}", sourceId, std::to_string(_hr));
        }

        return sourceId;
    }

    void XAudio2AudioProvider::SetSourceProperties(uint32_t sourceId, AudioSourceContext& context)
    {
        //volume
        if(FAILED(_hr = _sources.at(sourceId)->SetVolume(ConvertToXAudio2VolumeUnits(context.Volume))))
        {
            _logger->error("Error when setting volume for source {id} - Code: {hr}", sourceId, _hr);
        }
        //pitch
        if(FAILED(_hr = _sources.at(sourceId)->SetFrequencyRatio(context.Pitch)))
        {
            _logger->error("Error when setting pitch for source {id} - Code: {hr}", sourceId, _hr);
        }
    }

    AudioSourceState XAudio2AudioProvider::GetSourceState(uint32_t sourceId)
    {
        XAUDIO2_VOICE_STATE voiceState;
        _sources.at(sourceId)->GetState(&voiceState, 0);
        return ConvertToAudioSourceState(voiceState);
    }

    float XAudio2AudioProvider::ConvertToXAudio2VolumeUnits(float inputVolume)
    {
        return inputVolume * (XAUDIO2_MAX_VOLUME_LEVEL - (-XAUDIO2_MAX_VOLUME_LEVEL)) + -XAUDIO2_MAX_VOLUME_LEVEL;
    }

    AudioSourceState XAudio2AudioProvider::ConvertToAudioSourceState(XAUDIO2_VOICE_STATE sourceState)
    {
        switch(sourceState.BuffersQueued)
        {
            case NULL:
            {
                return AudioSourceState::SOURCE_STOPPED;
            }
            default:
            {
                return AudioSourceState::SOURCE_PLAYING;
            }
        }
    }
}
