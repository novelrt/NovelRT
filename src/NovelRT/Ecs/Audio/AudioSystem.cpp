// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Audio
{
    AudioSystem::AudioSystem()
        : _counter(1),
          _musicCache(std::map<uint32_t, std::vector<ALuint>::iterator>()),
          _soundCache(std::map<uint32_t, ALuint>()),
          _service(std::make_shared<NovelRT::Audio::AudioService>()),
          _logger(Utilities::Misc::CONSOLE_LOG_AUDIO)
    {
        _service->initializeAudio();
    }

    void AudioSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue catalogue)
    {
        auto emitters = catalogue.GetComponentView<AudioEmitterComponent>();

        for (auto [entity, emitter] : emitters)
        {
            switch (emitter.state)
            {
                case EmitterState::ToPlay:
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
                    emitters.PushComponentUpdateInstruction(
                        entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops,
                                                      emitter.position, emitter.volume, EmitterState::Playing});
                    break;
                }
                case EmitterState::ToStop:
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
                    emitters.PushComponentUpdateInstruction(
                        entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops,
                                                      emitter.position, emitter.volume, EmitterState::Stopped});
                    break;
                }
                case EmitterState::ToPause:
                {
                    // Sounds can't be paused so we just ignore that state.
                    if (emitter.isMusic)
                    {
                        _service->pauseMusic();
                        _logger.logDebug("Entity ID {} - EmitterState ToPause -> Paused", entity);
                        emitters.PushComponentUpdateInstruction(
                            entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops,
                                                          emitter.position, emitter.volume, EmitterState::Paused});
                    }
                    break;
                }
                case EmitterState::ToResume:
                {
                    if (emitter.isMusic)
                    {
                        _service->resumeMusic();
                        _logger.logDebug("Entity ID {} - EmitterState ToResume -> Playing", entity);
                        emitters.PushComponentUpdateInstruction(
                            entity, AudioEmitterComponent{emitter.handle, emitter.isMusic, emitter.numberOfLoops,
                                                          emitter.position, emitter.volume, EmitterState::Playing});
                    }
                    break;
                }
                case EmitterState::Playing:
                {
                    // check for volume changes
                    break;
                }
                case EmitterState::Stopped:
                case EmitterState::Paused:
                default:
                {
                    break;
                }
            }
        }

        _service->checkSources();
    }

    uint32_t AudioSystem::CreateAudio(std::string& fileName, bool isMusic)
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
}
