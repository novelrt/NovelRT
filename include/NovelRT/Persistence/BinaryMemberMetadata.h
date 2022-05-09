// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_BINARYMEMBERMETADATA_H
#define NOVELRT_PERSISTENCE_BINARYMEMBERMETADATA_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    struct BinaryMemberMetadata
    {
        std::string name;
        BinaryDataType type;
        size_t location;
        size_t sizeOfTypeInBytes;
        size_t length;
    };
}

#endif // NOVELRT_PERSISTENCE_BINARYMEMBERMETADATA_H
