#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <uuid.h>
#include <vector>

namespace NovelRT::ResourceManagement
{
    struct ScriptMetadata
    {
        bool isSource;
        std::vector<uint8_t> scriptCode;
        uuids::uuid databaseHandle;
    };
}
