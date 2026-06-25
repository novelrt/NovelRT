#pragma once

#include <cstdint>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::Audio::Components
{
    struct AudioEmitterComponent
    {
        uint32_t handle;
        bool isMusic;
        int32_t numberOfLoops;
        float volume;

        inline AudioEmitterComponent& operator+=(const AudioEmitterComponent& other) noexcept
        {
            bool handleChanged = (handle == other.handle);
            handle = handleChanged ? other.handle : handle;
            // isMusic should never change otherwise the component may be being abused.
            numberOfLoops = handleChanged ? other.numberOfLoops : numberOfLoops;
            volume = handleChanged ? other.volume : volume + other.volume;
            return *this;
        };

        [[nodiscard]] inline bool operator==(const AudioEmitterComponent& rhs) const noexcept
        {
            return handle == rhs.handle && isMusic == rhs.isMusic && numberOfLoops == rhs.numberOfLoops &&
                   volume == rhs.volume;
        }
    };
}
