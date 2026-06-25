#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Audio/AudioEmitterState.hpp>

namespace NovelRT::Ecs::Audio::Components
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

        [[nodiscard]] inline bool operator==(const AudioEmitterStateComponent& rhs) const noexcept
        {
            return state == rhs.state && fadeDuration == rhs.fadeDuration &&
                   fadeExpectedVolume == rhs.fadeExpectedVolume;
        }
    };
}
