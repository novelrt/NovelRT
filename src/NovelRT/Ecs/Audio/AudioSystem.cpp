// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Audio
{
    AudioSystem::AudioSystem()
        : _counter(1),
          _fadeCache(std::map<EntityId, std::tuple<Timing::Timestamp, float>>()),
          _logger(Utilities::Misc::CONSOLE_LOG_AUDIO),
          _musicCache(std::map<uint32_t, std::vector<ALuint>::iterator>()),
          _service(std::make_shared<NovelRT::Audio::AudioService>()),
          _soundCache(std::map<uint32_t, ALuint>()),
          _systemTime(Timing::Timestamp::zero())
    {
        _service->initializeAudio();
    }

    void AudioSystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        _systemTime += delta;
        auto [emitters, states] = catalogue.GetComponentViews<AudioEmitterComponent, AudioEmitterStateComponent>();

        for (auto [entity, emitterState] : states)
        {
            auto emitter = emitters.GetComponent(entity);

            switch (emitterState.state)
            {
                case AudioEmitterState::ToPlay:
                {
                    if (emitter.isMusic)
                    {
                        _service->playMusic(_musicCache.at(emitter.handle), emitter.numberOfLoops);
                    }
                    else
                    {
                        _service->playSound(_soundCache.at(emitter.handle), emitter.numberOfLoops);
                    }
                    _logger.logDebug("Entity ID {} - EmitterState ToPlay -> Playing", entity);
                    states.PushComponentUpdateInstruction(
                        entity, AudioEmitterStateComponent{AudioEmitterState::Playing, emitterState.fadeDuration});
                    break;
                }
                case AudioEmitterState::ToStop:
                {
                    if (emitter.isMusic)
                    {
                        _service->stopMusic();
                    }
                    else
                    {
                        _service->stopSound(_soundCache.at(emitter.handle));
                    }
                    _logger.logDebug("Entity ID {} - EmitterState ToStop -> Stopped", entity);
                    states.PushComponentUpdateInstruction(
                        entity, AudioEmitterStateComponent{AudioEmitterState::Stopped, emitterState.fadeDuration});
                    break;
                }
                case AudioEmitterState::ToPause:
                {
                    if (emitter.isMusic)
                    {
                        _service->pauseMusic();
                        _logger.logDebug("Entity ID {} - EmitterState ToPause -> Paused", entity);
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Paused, emitterState.fadeDuration});
                    }
                    break;
                }
                case AudioEmitterState::ToResume:
                {
                    if (emitter.isMusic)
                    {
                        _service->resumeMusic();
                        _logger.logDebug("Entity ID {} - EmitterState ToResume -> Playing", entity);
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Playing, emitterState.fadeDuration});
                    }
                    break;
                }
                case AudioEmitterState::ToFadeOut:
                {
                    if (emitter.isMusic && !_service->isMusicPlaying())
                    {
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Stopped, 0.0f, 0.0f});
                        break;
                    }
                    else if (!emitter.isMusic && !_service->isSoundPlaying(_soundCache.at(emitter.handle)))
                    {
                       states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Stopped, 0.0f, 0.0f});
                       break;
                    }

                    float slope = -(emitter.volume / emitterState.fadeDuration);
                    Timing::Timestamp endTime = _systemTime + Timing::Timestamp::fromSeconds(emitterState.fadeDuration);
                    _fadeCache.insert({entity, std::make_tuple(endTime, slope)});

                    states.PushComponentUpdateInstruction(
                        entity, AudioEmitterStateComponent{AudioEmitterState::FadingOut, emitterState.fadeDuration, 0.0f});
                    _logger.logDebug("Entity ID {} - EmitterState ToFadeOut -> FadingOut", entity);
                    break;
                }
                case AudioEmitterState::FadingOut:
                {
                    Timing::Timestamp endTime = std::get<0>(_fadeCache.at(entity));
                    float remainingDuration = (endTime - _systemTime).getSecondsFloat();

                    if(_systemTime < endTime)
                    {
                        float slope = std::get<1>(_fadeCache.at(entity));
                        float newVolume = emitter.volume + (slope * delta.getSecondsFloat());
                        ChangeAudioVolume(emitter, newVolume);
                        states.PushComponentUpdateInstruction(entity, AudioEmitterStateComponent{AudioEmitterState::FadingOut, remainingDuration, emitterState.fadeExpectedVolume});
                        emitters.PushComponentUpdateInstruction(entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, newVolume});
                        _logger.logDebug("Entity ID {} - EmitterState FadingOut at volume {}, slope: {}, currentTime: {}, remaining: {}", entity, newVolume, slope, _systemTime.getSecondsFloat(), remainingDuration);
                        break;
                    }
                    else
                    {
                        ChangeAudioVolume(emitter, 0.0f);
                        emitters.PushComponentUpdateInstruction(entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, emitterState.fadeExpectedVolume});
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
                    if (emitter.isMusic && !_service->isMusicPlaying())
                    {
                        _service->setMusicVolume(0.0f);
                        _service->playMusic(_musicCache.at(emitter.handle), emitter.numberOfLoops);
                    }
                    else if (!emitter.isMusic && !_service->isSoundPlaying(emitter.handle))
                    {
                        auto sound = _soundCache.at(emitter.handle);
                        _service->setSoundVolume(sound, 0.0f);
                        _service->playSound(sound, emitter.numberOfLoops);
                    }
                    else
                    {
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Playing, 0.0f, 0.0f});
                        break;
                    }

                    float slope = (emitter.volume / emitterState.fadeDuration);
                    Timing::Timestamp endTime = _systemTime + Timing::Timestamp::fromSeconds(emitterState.fadeDuration);
                    _fadeCache.insert({entity, std::make_tuple(endTime, slope)});

                    states.PushComponentUpdateInstruction(
                        entity, AudioEmitterStateComponent{AudioEmitterState::FadingIn, emitterState.fadeDuration, emitter.volume});
                    emitters.PushComponentUpdateInstruction(entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, 0.0f});
                    _logger.logDebug("Entity ID {} - EmitterState ToFadeIn -> FadingIn", entity);
                    break;
                }
                case AudioEmitterState::FadingIn:
                {
                    Timing::Timestamp endTime = std::get<0>(_fadeCache.at(entity));
                    float remainingDuration = (endTime - _systemTime).getSecondsFloat();

                    if(_systemTime < endTime)
                    {
                        float slope = std::get<1>(_fadeCache.at(entity));
                        float newVolume = emitter.volume + (slope * delta.getSecondsFloat());
                        ChangeAudioVolume(emitter, newVolume);
                        states.PushComponentUpdateInstruction(entity, AudioEmitterStateComponent{AudioEmitterState::FadingIn, remainingDuration, emitterState.fadeExpectedVolume});
                        emitters.PushComponentUpdateInstruction(entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, newVolume});
                        _logger.logDebug("Entity ID {} - EmitterState FadingIn at volume {}, slope: {}, currentTime: {}, remaining: {}", entity, newVolume, slope, _systemTime.getSecondsFloat(), remainingDuration);
                        break;
                    }
                    else
                    {
                        if(emitter.volume < emitterState.fadeExpectedVolume)
                        {
                            ChangeAudioVolume(emitter, emitterState.fadeExpectedVolume);
                        }
                        emitters.PushComponentUpdateInstruction(entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops, emitterState.fadeExpectedVolume});
                        states.PushComponentUpdateInstruction(
                            entity, AudioEmitterStateComponent{AudioEmitterState::Playing, 0.0f, 0.0f});
                        _fadeCache.erase(entity);
                        _logger.logDebug("Entity ID {} - EmitterState FadingIn -> Playing", entity);
                        break;
                    }
                }
                case AudioEmitterState::Playing:
                {
                    // check for volume changes
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

        _service->checkSources();
    }

    uint32_t AudioSystem::CreateAudio(std::string fileName, bool isMusic)
    {
        if (_counter == UINT32_MAX)
        {
            // add logging here
            return 0U;
        }

        // 0 is not valid here since we're working with only positive numbers... not that anyone should be loading
        // thousands of sounds.
        uint32_t value = 0U;
        if (isMusic)
        {
            auto handle = _service->loadMusic(fileName);
            if (_service->isLoaded(handle))
            {
                _musicCache.insert({_counter, handle});
                value = _counter;
                _counter++;
            }
        }
        else
        {
            auto handle = _service->loadSound(fileName);
            if (_service->isLoaded(handle))
            {
                _soundCache.insert({_counter, handle});
                value = _counter;
                _counter++;
            }
        }

        return value;
    }

    void AudioSystem::ChangeAudioVolume(AudioEmitterComponent emitter, float desiredVolume)
    {
        if(emitter.isMusic)
        {
            _service->setMusicVolume(desiredVolume);
        }
        else
        {
            _service->setSoundVolume(_soundCache.at(emitter.handle), desiredVolume);
        }
    }
}
