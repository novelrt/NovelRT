// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_BINARYPACKAGE_H
#define NOVELRT_PERSISTENCE_BINARYPACKAGE_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    struct BinaryPackage
    {
        std::vector<BinaryMemberMetadata> memberMetadata;
        std::vector<uint8_t> data;
    };
}

#endif // NOVELRT_PERSISTENCE_BINARYPACKAGE_H
