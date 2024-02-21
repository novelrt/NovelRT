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
    _impl(nullptr),
    _buffers(std::map<uint32_t, ::AVAudioPCMBuffer*>()),
    _sources(std::map<uint32_t, ::AVAudioPlayerNode*>()),
    _sourceEQUnits(std::map<uint32_t, ::AVAudioUnitEQ*>()),
    _sourceStates(std::map<uint32_t, AudioSourceState>()),
    _logger(spdlog::stdout_color_mt("AVAudioEngine"))
    {
        //Logger init
        _logger->set_level(spdlog::level::debug);
        
        //Device and Context Init
        @try 
        {
            ::NSError* err;
            _impl = [[::AVAudioEngine alloc] init];
            [(::AVAudioEngine*)_impl prepare];
            if([(::AVAudioEngine*)_impl startAndReturnError: &err])
            {
                _logger->error([err.localizedDescription UTF8String]);
                return;
            }
        }
        @catch(::NSException* ex)
        {
            std::string err = std::string([ex.reason UTF8String]);
            _logger->error(err);
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
    }

    uint32_t AVAudioEngineAudioProvider::OpenSource(AudioSourceContext& context)
    {
        uint32_t nextSource = ++_sourceCounter;
        ::AVAudioPlayerNode* node = [[::AVAudioPlayerNode alloc] init];
        [(::AVAudioEngine*)_impl attachNode:node];
        _sources.emplace(nextSource, node);
        _sourceStates.emplace(nextSource, AudioSourceState::SOURCE_STOPPED);

        ::AVAudioUnitEQ* eq = [[::AVAudioUnitEQ alloc] initWithNumberOfBands: 1];
        [(::AVAudioEngine*)_impl attachNode:eq];
        _sourceEQUnits.emplace(nextSource, eq);

        ::AVAudioFormat* format = [[::AVAudioFormat alloc] initWithCommonFormat:AVAudioCommonFormat::AVAudioPCMFormatInt16 sampleRate:context.SampleRate channels:context.Channels interleaved:false];
        ::AVAudioMixerNode* mixerNode = ((::AVAudioEngine*)_impl).mainMixerNode;
        [(::AVAudioEngine*)_impl connect:node to:eq format:format];
        [(::AVAudioEngine*)_impl connect:eq to:mixerNode format:format];
        
        return nextSource;
    }

    void AVAudioEngineAudioProvider::PlaySource(uint32_t sourceId)
    {
        ::AVAudioPlayerNode* node = _sources.at(sourceId);
        
        if(!node.playing)
        {
            [(::AVAudioPlayerNode*)node play];
        }
        
        
        _sourceStates[sourceId] = AudioSourceState::SOURCE_PLAYING;

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

    uint32_t AVAudioEngineAudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context)
    {
        ::AVAudioFormat* format = [[::AVAudioFormat alloc] initWithCommonFormat:AVAudioCommonFormat::AVAudioPCMFormatInt16 sampleRate:context.SampleRate channels:context.Channels interleaved:false];
        AudioBufferList abl;
        abl.mNumberBuffers = 1;
        abl.mBuffers[0].mData = (void *)buffer.data();
        abl.mBuffers[0].mNumberChannels = context.Channels;
        abl.mBuffers[0].mDataByteSize = buffer.size() * sizeof(int16_t);
        ::AVAudioPCMBuffer* pcmBuffer = [[::AVAudioPCMBuffer alloc] initWithPCMFormat:format bufferListNoCopy:&abl deallocator:NULL];
        
        uint32_t sourceId = OpenSource(context);
        
        ::AVAudioPlayerNode* node = _sources.at(sourceId);
        // AVAudioPlayerNodeBufferOptions options = AVAudioPlayerNodeBufferLoops;

        if(context.Loop)
        {
            [(::AVAudioPlayerNode*)node scheduleBuffer: pcmBuffer atTime: nil options: AVAudioPlayerNodeBufferLoops completionCallbackType: AVAudioPlayerNodeCompletionDataPlayedBack completionHandler: nil];
        }
        else
        {
            [(::AVAudioPlayerNode*)node scheduleBuffer: pcmBuffer completionHandler: nil];
        }
        _buffers.emplace(sourceId, pcmBuffer);

        return sourceId;
    }

    void AVAudioEngineAudioProvider::SetSourceProperties(uint32_t sourceId, AudioSourceContext& context)
    {
        ::AVAudioUnitEQ* eq = _sourceEQUnits.at(sourceId);
        eq.globalGain = context.Volume;
    }

    AudioSourceState AVAudioEngineAudioProvider::GetSourceState(uint32_t sourceId)
    {
        return _sourceStates.at(sourceId);
    }

    

    
}
