// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/AudioMixer.hpp>

//Conditional
#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>

namespace NovelRT::Audio
{
    void AudioMixer::Initialise()
    {
        _audioProvider = std::make_unique<OpenAL::OpenALAudioProvider>();
        _audioProvider->OpenOutputStream();
    }

    void AudioMixer::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer)
    {
        _audioProvider->SubmitAudioBuffer(buffer);
    }

    void AudioMixer::PlayOutputStream()
    {
        _audioProvider->PlayOutputStream();
    }

    void AudioMixer::StopOutputStream()
    {
        _audioProvider->StopOutputStream();
    }

    void AudioMixer::TearDown()
    {
        _audioProvider->CloseOutputStream();
        _audioProvider.reset();
    }

    AudioMixer::~AudioMixer()
    {
        TearDown();
    }
}
