// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Exceptions/Exceptions.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#import <NovelRT/Audio/AVAudioEngine/AVAudioEngineAudioProvider.hpp>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFAudio/AVAudioEngine.h>

namespace NovelRT::Audio::AVAudioEngine
{
    AVAudioEngineAudioProvider::AVAudioEngineAudioProvider():
    _buffers(std::map<uint32_t, ::AVAudioPCMBuffer*>()),
    _sources(std::map<uint32_t, ::AVAudioPlayerNode*>()),
    _sourceEQUnits(std::map<uint32_t, ::AVAudioUnitEQ*>()),
    _sourceStates(std::map<uint32_t, AudioSourceState>()),
    _sourceContexts(std::map<uint32_t, AudioSourceContext>()),
    _logger(spdlog::stdout_color_mt("AVAudioEngine"))
    {
        //Logger init
        _logger->set_level(spdlog::level::debug);

        //Device and Context Init
        @try
        {
            ::NSError* err;
            _logger->debug("calling alloc and init");
            _impl = [::AVAudioEngine new];
        }
        @catch(::NSException* ex)
        {
            std::string err = std::string([ex.reason UTF8String]);
            _logger->error(err);
            throw new Exceptions::InitialisationFailureException("Failed to initialise AVAudioEngine!", err);
        }
    }

    AVAudioEngineAudioProvider::~AVAudioEngineAudioProvider()
    {
        Dispose();
        [(::AVAudioEngine*)_impl stop];
        [(::AVAudioEngine*)_impl release];
    }

    void AVAudioEngineAudioProvider::Dispose()
    {
        for(auto [id, source] : _sources)
        {
            [(::AVAudioPlayerNode*)source stop];
            [(::AVAudioPlayerNode*)source release];
        }
        _sources.clear();

        for(auto [id, source] : _sourceEQUnits)
        {
            [(::AVAudioUnitEQ*)source release];
        }
        _sourceEQUnits.clear();

        for(auto [id, buffer] : _buffers)
        {
            [(::AVAudioPCMBuffer*)buffer release];
        }
        _buffers.clear();

        _sourceContexts.clear();
    }

    uint32_t AVAudioEngineAudioProvider::OpenSource(AudioSourceContext& context)
    {
        unused(context);
        return _sourceCounter;
    }

    uint32_t AVAudioEngineAudioProvider::OpenSourceInternal(AudioSourceContext& context, ::AVAudioPCMBuffer* buffer, ::AVAudioFormat* format)
    {
        uint32_t nextSource = ++_sourceCounter;
        ::AVAudioPlayerNode* node = [::AVAudioPlayerNode new];
        [_impl attachNode:node];
        _sources.emplace(nextSource, node);
        _sourceStates.emplace(nextSource, AudioSourceState::SOURCE_STOPPED);
        _sourceContexts.emplace(nextSource, context);

        ::AVAudioUnitEQ* eq = [[::AVAudioUnitEQ alloc] initWithNumberOfBands: 1];
        [_impl attachNode:eq];
        _sourceEQUnits.emplace(nextSource, eq);

        _logger->debug("Connecting source {0} to EQ", nextSource);
        [(::AVAudioEngine*)_impl connect:node to:eq format:nil];
        _logger->debug("Connecting source {0} EQ to mixer", nextSource);
        [(::AVAudioEngine*)_impl connect:eq to:_impl.mainMixerNode format:nil];
        _buffers.emplace(nextSource, buffer);

        return nextSource;
    }

    void AVAudioEngineAudioProvider::PlaySource(uint32_t sourceId)
    {
        if(!_impl.running)
        {
            _logger->debug("filling up gas tank...");
            [(::AVAudioEngine*)_impl prepare];
            ::NSError* err;
            _logger->debug("starting engine.... VRROOOOOOOMMMMM....");
            [_impl startAndReturnError: &err];
            if(!_impl.running)
            {
                _logger->error("Could not start engine: {0}", std::string([err.localizedDescription UTF8String]));
            }
        }

        ::AVAudioPlayerNode* node = _sources.at(sourceId);

        if(!node.playing)
        {
            auto lambda = [this, sourceId = sourceId]()
            {
                this->UpdateSourceState(sourceId, AudioSourceState::SOURCE_STOPPED);
            };
            if(_sourceContexts.at(sourceId).Loop)
            {
                _logger->debug("Looping source ID {0}", sourceId);
                [node scheduleBuffer: _buffers.at(sourceId) atTime: nil options: AVAudioPlayerNodeBufferLoops completionHandler: nil];
            }
            else
            {
                [node scheduleBuffer: _buffers.at(sourceId) completionHandler: lambda];
            }


            
            
            [node play];
        }

        _sourceStates[sourceId] = AudioSourceState::SOURCE_PLAYING;
    }

    void AVAudioEngineAudioProvider::UpdateSourceState(uint32_t sourceId, AudioSourceState state)
    {
        _sourceStates[sourceId] = state;
    }

    void AVAudioEngineAudioProvider::StopSource(uint32_t sourceId)
    {
        ::AVAudioPlayerNode* node = _sources.at(sourceId);
        if(node.playing)
        {
            [(::AVAudioPlayerNode*)node stop];
        }
        _sourceStates[sourceId] = AudioSourceState::SOURCE_STOPPED;
    }

    void AVAudioEngineAudioProvider::PauseSource(uint32_t sourceId)
    {
        ::AVAudioPlayerNode* node = _sources.at(sourceId);
        if(node.playing)
        {
            [(::AVAudioPlayerNode*)node pause];
        }
        _sourceStates[sourceId] = AudioSourceState::SOURCE_PAUSED;
    }

    uint32_t AVAudioEngineAudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<float> buffer, AudioSourceContext& context)
    {
        _logger->debug("Loading audio buffer - SampleRate: {0}, Channels: {1}", context.SampleRate, context.Channels);
        
        uint32_t frameCap = buffer.size() * sizeof(float);
        ::AVAudioFormat* format = [[::AVAudioFormat alloc] initWithCommonFormat:AVAudioCommonFormat::AVAudioPCMFormatFloat32 sampleRate:44100 channels:context.Channels interleaved:true];
        ::AVAudioFormat* deformat = [[::AVAudioFormat alloc] initWithCommonFormat:AVAudioCommonFormat::AVAudioPCMFormatFloat32 sampleRate:44100 channels:context.Channels interleaved:false];
        AudioBufferList abl;
        abl.mNumberBuffers = 1;
        abl.mBuffers[0].mData = ((void *)new Byte[frameCap]);
        abl.mBuffers[0].mNumberChannels = context.Channels;
        abl.mBuffers[0].mDataByteSize = frameCap;

        std::memcpy((void*)abl.mBuffers[0].mData, reinterpret_cast<void*>(buffer.data()), frameCap);

        ::AVAudioPCMBuffer* pcmBuffer = [[::AVAudioPCMBuffer alloc] initWithPCMFormat:format bufferListNoCopy:&abl deallocator:NULL];

        ::AVAudioConverter* convert = [[::AVAudioConverter alloc] initFromFormat:format toFormat:deformat];
        ::AVAudioPCMBuffer* deinterleavedBuffer = [[::AVAudioPCMBuffer alloc] initWithPCMFormat:deformat frameCapacity:pcmBuffer.frameCapacity];
        [convert convertToBuffer:deinterleavedBuffer fromBuffer:pcmBuffer error:nil];
        
        return OpenSourceInternal(context, deinterleavedBuffer, format);
    }

    void AVAudioEngineAudioProvider::SetSourceProperties(uint32_t sourceId, AudioSourceContext& context)
    {
        _sourceContexts[sourceId] = context;

        ::AVAudioUnitEQ* eq = _sourceEQUnits.at(sourceId);
        eq.globalGain = context.Volume;
    }

    AudioSourceState AVAudioEngineAudioProvider::GetSourceState(uint32_t sourceId)
    {
        return _sourceStates.at(sourceId);
    }
}
