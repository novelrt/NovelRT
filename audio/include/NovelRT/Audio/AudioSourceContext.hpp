// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <cstdint>

namespace NovelRT::Audio
{
    struct AudioSourceContext
    {
        public:
            float Volume = 0.75f;
            float Pitch = 1.0f;
            bool Loop = false;
    };
}
