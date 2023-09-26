// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_IAUDIOIMPL_HPP
#define NOVELRT_AUDIO_IAUDIOIMPL_HPP

namespace NovelRT::Audio
{
    struct IAudioImpl
    {
        virtual void Update(float delta) = 0;
        virtual void Init() = 0;
        virtual void Shutdown() = 0;
        virtual void MuteAll() = 0;
        virtual void UnmuteAll() = 0;
        virtual ISound* LoadSound(const std::string& name);
        virtual void UnloadSound(const ISound& sound);
        virtual int32_t RegisterObject(IAudioObject& object, std::string& name) = 0;
        virtual void UnregisterObject() = 0;
        virtual IAudioListener CreateListener() = 0;
        virtual void DestroyListener() = 0;
        virtual bool IsPlaying(const ISound& sound) = 0;
        virtual ~IAudioImpl() = 0;
    };
}

#endif // NOVELRT_AUDIO_IAUDIOIMPL_HPP
