#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>
#include <uuid.h>
#include <vector>

namespace NovelRT::ResourceManagement
{
    struct AudioMetadata
    {
        std::vector<float> processedAudioFrames;
        int32_t channelCount;
        int32_t sampleRate;
        uuids::uuid databaseHandle;
    };
}
