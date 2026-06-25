#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

#include <NovelRT/Audio/AudioMixer.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Audio/Components/AudioEmitterComponent.hpp>
#include <NovelRT/Ecs/Audio/Components/AudioEmitterStateComponent.hpp>
#include <NovelRT/Ecs/Audio/AudioEmitterState.hpp>

#include <NovelRT/Logging/LoggingService.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>

#include <NovelRT/ResourceManagement/ResourceLoader.hpp>
#include <NovelRT/Utilities/Span.hpp>

using namespace NovelRT::Ecs::Audio::Components;

namespace NovelRT::Ecs::Audio
{

    template<typename TAudioBackend>
    class AudioSystem : public Ecs::IEcsSystem
    {
    private:
        uint32_t _counter;
        NovelRT::Logging::LoggingService _logger;
        std::map<uint32_t, NovelRT::ResourceManagement::AudioMetadata> _soundCache;
        std::map<EntityId, std::tuple<NovelRT::Timing::Timestamp, float>> _fadeCache;
        std::shared_ptr<NovelRT::Audio::AudioMixer<TAudioBackend>> _mixer;
        NovelRT::Timing::Timestamp _systemTime;
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> _resourceLoader;

        void ChangeAudioVolume(AudioEmitterComponent emitter, float desiredVolume)
        {
            _mixer->SetSourceVolume(emitter.handle, desiredVolume);
        }

    public:
        AudioSystem(std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> resourceLoader, std::shared_ptr<NovelRT::Audio::AudioProvider<TAudioBackend>> provider):
            _counter(1),
            _logger(NovelRT::Logging::CONSOLE_LOG_AUDIO),
            _soundCache(std::map<uint32_t, NovelRT::ResourceManagement::AudioMetadata>()),
            _fadeCache(std::map<EntityId, std::tuple<NovelRT::Timing::Timestamp, float>>()),
            _mixer(std::make_shared<NovelRT::Audio::AudioMixer<TAudioBackend>>(provider)),
            _systemTime{},
            _resourceLoader(std::move(resourceLoader))
        {
        }
        
        ~AudioSystem() noexcept
        {
            unused(_soundCache.empty());
        }

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final
        {
            _systemTime += delta.time_since_epoch();
            auto [emitters, states] = catalogue.GetComponentViews<AudioEmitterComponent, AudioEmitterStateComponent>();

            for (auto [entity, emitterState] : states)
            {
                auto emitter = emitters.GetComponent(entity);

                switch (emitterState.state)
                {
                    case AudioEmitterState::ToPlay:
                    {
                        _mixer->SetSourceLoop(emitter.handle, emitter.numberOfLoops > 0);
                        _mixer->PlaySource(emitter.handle);
                        _logger.logDebug("Entity ID {} - EmitterState ToPlay -> Playing", entity);
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Playing, emitterState.fadeDuration});
                        break;
                    }
                    case AudioEmitterState::ToStop:
                    {
                        _mixer->StopSource(emitter.handle);
                        _logger.logDebug("Entity ID {} - EmitterState ToStop -> Stopped", entity);
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Stopped, emitterState.fadeDuration});
                        break;
                    }
                    case AudioEmitterState::ToPause:
                    {
                        _mixer->PauseSource(emitter.handle);
                        _logger.logDebug("Entity ID {} - EmitterState ToPause -> Paused", entity);
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Paused, emitterState.fadeDuration});
                        break;
                    }
                    case AudioEmitterState::ToResume:
                    {
                        _mixer->PlaySource(emitter.handle);
                        _logger.logDebug("Entity ID {} - EmitterState ToResume -> Playing", entity);
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Playing, emitterState.fadeDuration});
                        break;
                    }
                    case AudioEmitterState::ToFadeOut:
                    {
                        if (_mixer->GetSourceState(emitter.handle) == NovelRT::Audio::AudioSourceState::SOURCE_STOPPED)
                        {
                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::Stopped, 0.0f, 0.0f});
                            break;
                        }

                        float slope = -(emitter.volume / emitterState.fadeDuration);
                        Timing::Timestamp endTime = _systemTime + Timing::TimeFromSeconds(emitterState.fadeDuration).time_since_epoch();
                        _fadeCache.insert({entity, std::make_tuple(endTime, slope)});

                        states.PushComponentUpdateInstruction(
                            entity,
                            AudioEmitterStateComponent{AudioEmitterState::FadingOut, emitterState.fadeDuration, 0.0f});
                        _logger.logDebug("Entity ID {} - EmitterState ToFadeOut -> FadingOut", entity);
                        break;
                    }
                    case AudioEmitterState::FadingOut:
                    {
                        Timing::Timestamp endTime = std::get<0>(_fadeCache.at(entity));
                        float remainingDuration = Timing::GetSeconds<float>(endTime - _systemTime);

                        if (_systemTime < endTime)
                        {
                            float slope = std::get<1>(_fadeCache.at(entity));
                            float newVolume = emitter.volume + (slope * Timing::GetSeconds<float>(delta));
                            _mixer->SetSourceVolume(emitter.handle, newVolume);

                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::FadingOut, remainingDuration,
                                                                emitterState.fadeExpectedVolume});
                            emitters.PushComponentUpdateInstruction(
                                entity,
                                AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, newVolume});
                            _logger.logDebug("Entity ID {} - EmitterState FadingOut at volume {}, slope: {}, currentTime: "
                                            "{}, remaining: {}",
                                            entity, newVolume, slope, Timing::GetSeconds<float>(_systemTime), remainingDuration);
                            break;
                        }
                        else
                        {
                            _mixer->SetSourceVolume(emitter.handle, 0.0f);
                            _mixer->StopSource(emitter.handle);

                            emitters.PushComponentUpdateInstruction(
                                entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops,
                                                            emitterState.fadeExpectedVolume});
                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::Stopped, 0.0f, 0.0f});
                            _fadeCache.erase(entity);
                            _logger.logDebug("Entity ID {} - EmitterState FadingOut -> Stopped", entity);
                            break;
                        }

                        break;
                    }
                    case AudioEmitterState::ToFadeIn:
                    {
                        if (_mixer->GetSourceState(emitter.handle) == NovelRT::Audio::AudioSourceState::SOURCE_STOPPED)
                        {
                            _mixer->SetSourceVolume(emitter.handle, 0.0f);
                            _mixer->PlaySource(emitter.handle);
                        }
                        else
                        {
                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::Playing, 0.0f, 0.0f});
                            break;
                        }

                        float slope = (emitterState.fadeExpectedVolume / emitterState.fadeDuration);
                        Timing::Timestamp endTime = _systemTime + Timing::TimeFromSeconds(emitterState.fadeDuration).time_since_epoch();
                        _fadeCache.insert({entity, std::make_tuple(endTime, slope)});

                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::FadingIn, emitterState.fadeDuration,
                                                            emitterState.fadeExpectedVolume});
                        emitters.PushComponentUpdateInstruction(
                            entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, 0.0f});
                        _logger.logDebug("Entity ID {} - EmitterState ToFadeIn -> FadingIn", entity);
                        break;
                    }
                    case AudioEmitterState::FadingIn:
                    {
                        Timing::Timestamp endTime = std::get<0>(_fadeCache.at(entity));
                        float remainingDuration = Timing::GetSeconds<float>(endTime - _systemTime);

                        if (_systemTime < endTime)
                        {
                            float slope = std::get<1>(_fadeCache.at(entity));
                            float newVolume = emitter.volume + (slope * Timing::GetSeconds<float>(delta));
                            _mixer->SetSourceVolume(emitter.handle, newVolume);
                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::FadingIn, remainingDuration,
                                                                emitterState.fadeExpectedVolume});
                            emitters.PushComponentUpdateInstruction(
                                entity,
                                AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, newVolume});
                            _logger.logDebug("Entity ID {} - EmitterState FadingIn at volume {}, slope: {}, currentTime: "
                                            "{}, remaining: {}",
                                            entity, newVolume, slope, Timing::GetSeconds<float>(_systemTime), remainingDuration);
                            break;
                        }
                        else
                        {
                            if (emitter.volume < emitterState.fadeExpectedVolume)
                            {
                                _mixer->SetSourceVolume(emitter.handle, emitterState.fadeExpectedVolume);
                            }
                            emitters.PushComponentUpdateInstruction(
                                entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops,
                                                            emitterState.fadeExpectedVolume});
                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::Playing, 0.0f, 0.0f});
                            _fadeCache.erase(entity);
                            _logger.logDebug("Entity ID {} - EmitterState FadingIn -> Playing", entity);
                            break;
                        }
                    }
                    case AudioEmitterState::Playing:
                    {
                        auto soundContext = _mixer->GetSourceContext(emitter.handle);
                        if (soundContext.Volume != emitter.volume)
                        {
                            _mixer->SetSourceVolume(emitter.handle, emitter.volume);
                            _logger.logDebug("Entity ID {} - Emitter Volume {} -> {}", entity, soundContext.Volume,
                                            emitter.volume);
                        }
                        if (_mixer->GetSourceState(emitter.handle) != NovelRT::Audio::AudioSourceState::SOURCE_PLAYING)
                        {
                            states.PushComponentUpdateInstruction(
                                entity, AudioEmitterStateComponent{AudioEmitterState::ToStop, 0.0f, 0.0f});
                        }
                        break;
                    }
                    case AudioEmitterState::Stopped:
                    case AudioEmitterState::Paused:
                    default:
                    {
                        break;
                    }
                }
            }
        }
        
        uint32_t RegisterSound(std::string fileName)
        {
            if (_counter == UINT32_MAX)
            {
                return 0U;
            }

            auto asset = _resourceLoader->LoadAudioFrameData(fileName);
            auto handle = _mixer->SubmitAudioBuffer(
                NovelRT::Utilities::Span<float>(asset.processedAudioFrames.data(), asset.processedAudioFrames.size()),
                asset.channelCount, asset.sampleRate);
            _soundCache.emplace(handle, asset);
            _counter++;
            return handle;
        }
    };
}
