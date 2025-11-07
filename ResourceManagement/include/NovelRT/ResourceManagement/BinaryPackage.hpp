#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vector>
#include <cstdint>
#include <uuid.h>

#include <NovelRT/ResourceManagement/BinaryMemberMetadata.hpp>

namespace NovelRT::ResourceManagement
{
    struct BinaryPackage
    {
        std::vector<BinaryMemberMetadata> memberMetadata;
        std::vector<uint8_t> data;
        uuids::uuid databaseHandle;
    };
}
