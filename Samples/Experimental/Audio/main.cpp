// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/AudioProvider.hpp>
#include <NovelRT/Exceptions/FileNotFoundException.hpp>
#include <NovelRT/Utilities/Paths.hpp>

#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace NovelRT::Audio;

constexpr float PI = 3.14159265f;

int main()
{
    auto provider = std::make_shared<AudioProvider<OpenAL::OpenALAudioBackend>>();

    std::vector<float> samples(48'000);
    std::generate(samples.begin(), samples.end(), [rate = samples.size(), freq = 440, n = 0]() mutable {
        float t = float(n++) / rate;
        return std::sin(freq * 2.f * PI * t);
    });

    AudioSourceContext sineWave{};
    sineWave.Loop = true;
    sineWave.Volume = 0.1f;
    sineWave.Channels = 1;
    sineWave.SampleRate = samples.size();

    uint32_t sineWaveId = provider->SubmitAudioBuffer(samples, sineWave);

    provider->PlaySource(sineWaveId);

    std::cout << "Playing a sine wave. Press any key to stop.\n";

    std::string ignored;
    std::getline(std::cin, ignored);
}
