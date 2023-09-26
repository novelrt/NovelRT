// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/Audio.hpp>

namespace NovelRT::Audio
{
    AudioEngine::AudioEngine() : _soundMap(std::map<int32_t, ISound*>()),
        _currentId(0)
    {
        //_impl = &impl;
    }

    void AudioEngine::Initialise()
    {
        _impl->Init();
        //set listener
    }

    void AudioEngine::Update(float delta)
    {
        _impl->Update(delta);
    }

    void AudioEngine::Teardown()
    {
        delete _impl;
    }

    void AudioEngine::PlaySound(int32_t soundId, float decibelVolume)
    {
        unused(soundId);
        unused(decibelVolume);
    }

    void AudioEngine::StopSound(int32_t soundId)
    {
unused(soundId);
    }

    void AudioEngine::PauseSound(int32_t soundId)
    {
unused(soundId);
    }

    void AudioEngine::SetSoundVolume(int32_t soundId, float decibelVolume)
    {
        unused(soundId);
        unused(decibelVolume);
    }

    void AudioEngine::SetListenerPosition(const NovelRT::Maths::GeoVector2F& position)
    {
        _listener.position = position;
    }

    void AudioEngine::SetListenerPosition(float x, float y)
    {
        _listener.position.x = x;
        _listener.position.y = y;
    }

    int32_t AudioEngine::LoadSound(const std::string& name)
    {
        ISound* sound = _impl->LoadSound(name);
        if(sound != nullptr)
        {
            _soundMap.emplace(std::pair<int32_t, ISound*>(_currentId, sound));
            _currentId++;
            return _currentId - 1;
        }

        return GENERIC_ERROR;
    }

    void AudioEngine::UnloadSound(int32_t soundId)
    {
        auto it = _soundMap.find(soundId);
        if(it != _soundMap.end())
        {
            _impl->UnloadSound(*it->second);
        }
    }

    bool AudioEngine::IsPlaying(int32_t soundId) const
    {
        auto it = _soundMap.find(soundId);
        if(it != _soundMap.end())
        {
            return _impl->IsPlaying(*it->second);
        }

        return false;
    }


}
