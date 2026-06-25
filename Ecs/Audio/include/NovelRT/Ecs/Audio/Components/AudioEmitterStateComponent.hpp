#pragma once

#include <NovelRT/Ecs/Audio/AudioEmitterState.hpp>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::Audio
{
    struct AudioEmitterStateComponent
    {
        AudioEmitterState state = AudioEmitterState::Stopped;
        float fadeDuration = 0;
        float fadeExpectedVolume = 0;

        inline AudioEmitterStateComponent& operator+=(const AudioEmitterStateComponent& other) noexcept
        {
            state = other.state;
            fadeDuration = other.fadeDuration;
            fadeExpectedVolume = other.fadeExpectedVolume;
            return *this;
        };

        [[nodiscard]] inline bool operator==(const AudioEmitterStateComponent& rhs) noexcept
        {
            return state == rhs.state && fadeDuration == rhs.fadeDuration &&
                   fadeExpectedVolume == rhs.fadeExpectedVolume;
        }
    };
}
