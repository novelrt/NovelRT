// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <NovelRT/Audio/IAudioProvider.hpp>
#include <vector>
#include <map>
#include <spdlog/spdlog.h>


#ifdef __OBJC__
    @class AVAudioEngine;
    @class AVAudioPlayerNode;
    @class AVAudioPCMBuffer;
    @class AVAudioUnitEQ;
    @class AVAudioFormat;
    ::AVAudioEngine* _impl;     // represents Obj-C object
    ::AVAudioFormat* _mixerFormat;
#else
    typedef struct objc_object AVAudioEngine;
    typedef struct objc_object AVAudioPlayerNode;
    typedef struct objc_object AVAudioPCMBuffer;
    typedef struct objc_object AVAudioUnitEQ;
    typedef struct objc_object AVAudioFormat;
#endif



namespace NovelRT::Audio::AVAudioEngine
{
    class AVAudioEngineAudioProvider : public IAudioProvider
    {
        private:
            
            std::map<uint32_t, ::AVAudioPlayerNode*> _sources;
            std::map<uint32_t, ::AVAudioUnitEQ*> _sourceEQUnits;
            std::map<uint32_t, ::AVAudioPCMBuffer*> _buffers;
            std::map<uint32_t, AudioSourceState> _sourceStates;
            std::shared_ptr<spdlog::logger> _logger;
            uint32_t _sourceCounter = 0;

            uint32_t OpenSourceInternal(AudioSourceContext& context, ::AVAudioPCMBuffer* buffer, ::AVAudioFormat* format);

        protected:
            void Dispose() final;
            uint32_t OpenSource(AudioSourceContext& context) final;

        public:
            AVAudioEngineAudioProvider();
            void PlaySource(uint32_t sourceId) final;
            void StopSource(uint32_t sourceId) final;
            void PauseSource(uint32_t sourceId) final;
            void SetSourceProperties(uint32_t sourceId, AudioSourceContext& context) final;
            uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context) final;
            AudioSourceState GetSourceState(uint32_t id) final;

            ~AVAudioEngineAudioProvider() final;
    };
}
