// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_AUDIOENGINE_H
#define NOVELRT_AUDIO_AUDIOENGINE_H

namespace NovelRT::Audio
{
    class AudioEngine
    {
        private:
            const int32_t GENERIC_ERROR = -1;
            IAudioImpl* _impl;
            IAudioListener _listener;
            std::map<int32_t, ISound*> _soundMap;
            int32_t _currentId;

        public:
            bool initialised = false;

            AudioEngine();
            void Initialise();
            void Update(float delta);
            void Teardown();
            void PlaySound(int32_t soundId, float decibelVolume = 0.0f);
            void StopSound(int32_t soundId);
            void PauseSound(int32_t soundId);
            void SetSoundVolume(int32_t soundId, float decibelVolume);
            void SetListenerPosition(const NovelRT::Maths::GeoVector2F& position);
            void SetListenerPosition(float x, float y);
            int32_t LoadSound(const std::string& name);
            void UnloadSound(int32_t soundId);
            bool IsPlaying(int32_t soundId) const;

    };
}

#endif // NOVELRT_AUDIO_AUDIOENGINE_H
