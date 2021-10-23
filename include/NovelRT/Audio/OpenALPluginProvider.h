// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_OPENALPLUGINPROVIDER_H
#define NOVELRT_AUDIO_OPENALPLUGINPROVIDER_H

//#ifndef NOVELRT_EXPERIMENTAL_Audio_GLFW_H
//#error NovelRT does not support including types explicitly by default. Please include Audio.Glfw.h instead for the Audio::Glfw namespace subset.
//#endif

namespace NovelRT::Audio
{
    class OpenALPluginProvider final : public PluginManagement::IAudioPluginProvider
    {
    private:
        std::shared_ptr<AudioService> _AudioService;

        [[nodiscard]] Audio::AudioService* GetAudioDeviceInternal() override;

    public:
        OpenALPluginProvider() noexcept;

        [[nodiscard]] inline std::shared_ptr<AudioService> GetAudioDevice()
        {
            return std::dynamic_pointer_cast<AudioService>(GetAudioDeviceInternal()->shared_from_this());
        }
    };
}

#endif // NOVELRT_AUDIO_OPENALPLUGINPROVIDER_H
