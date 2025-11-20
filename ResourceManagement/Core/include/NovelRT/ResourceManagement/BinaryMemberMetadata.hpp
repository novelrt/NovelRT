#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <string>
#include <cstdint>
#include <NovelRT/ResourceManagement/BinaryDataType.hpp>

namespace NovelRT::ResourceManagement
{
    struct BinaryMemberMetadata
    {
        std::string name;
        BinaryDataType type;
        size_t location;
        size_t sizeOfTypeInBytes;
        size_t length;
        size_t sizeOfSerialisedDataInBytes;
    };
}
