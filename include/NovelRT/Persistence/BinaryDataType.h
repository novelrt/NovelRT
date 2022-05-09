// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_BINARYDATATYPE_H
#define NOVELRT_PERSISTENCE_BINARYDATATYPE_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    enum class BinaryDataType : uint32_t
    {
        Null = 0,
        Boolean = 1,
        Int32 = 2,
        Int64 = 3,
        UInt32 = 4,
        UInt64 = 5,
        Double = 6,
        String = 7,
        Binary = 8
    };
}

#endif // NOVELRT_PERSISTENCE_BINARYDATATYPE_H
