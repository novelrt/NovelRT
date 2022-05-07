// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IPERSISTABLE_H
#define NOVELRT_IPERSISTABLE_H

namespace NovelRT::Persistence
{
    class IPersistable
    {
    public:
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

        struct BinaryMemberMetadata
        {
            std::string name;
            BinaryDataType type;
            size_t location;
            size_t sizeOfTypeInBytes;
            size_t length;
        };

        struct BinaryPackage
        {
            std::vector<BinaryMemberMetadata> memberMetadata;
            std::vector<uint8_t> data;
        };

        [[nodiscard]] virtual BinaryPackage ToFileData() const noexcept = 0;
        virtual void LoadFileData(const BinaryPackage& data) noexcept = 0;
    };
}

#endif // NOVELRT_IPERSISTABLE_H
