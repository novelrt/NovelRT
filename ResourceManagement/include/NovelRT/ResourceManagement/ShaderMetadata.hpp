#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vector>
#include <uuid.h>

namespace NovelRT::ResourceManagement
{
    struct ShaderMetadata
    {
        std::vector<uint8_t> shaderCode;
        uuids::uuid databaseHandle;
    };
}
