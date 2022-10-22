// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <gtest/gtest.h>

class InteropBinaryMemberMetadataTest : public testing::Test
{
protected:

    NrtBinaryMemberMetadataCreateInfo DummyInfo {
        "test",
        NRT_BINTYPE_NULLORUNKNOWN,
        10,
        20,
        30,
        40
    };

    NrtBinaryMemberMetadataHandle DummyHandle = nullptr;

    void SetUp() override
    {
        DummyHandle = Nrt_BinaryMemberMetadata_Create(DummyInfo);
    }

    void TearDown() override
    {
        static_cast<void>(Nrt_BinaryMemberMetadata_Destroy(DummyHandle));
    }
};

TEST_F(InteropBinaryMemberMetadataTest, CreateReturnsValidHandle)
{
    NrtBinaryMemberMetadataCreateInfo info {
        "test",
        NRT_BINTYPE_NULLORUNKNOWN,
        0,
        0,
        0,
        0
    };

    auto handle = Nrt_BinaryMemberMetadata_Create(info);

    EXPECT_NE(handle, nullptr);
}

TEST_F(InteropBinaryMemberMetadataTest, GetNameReturnsCorrectName)
{
    EXPECT_EQ(strcmp("test", Nrt_BinaryMemberMetadata_GetName(DummyHandle)), 0);
}

TEST_F(InteropBinaryMemberMetadataTest, GetBinaryDataTypeReturnsCorrectTypeEnum)
{
    EXPECT_EQ(Nrt_BinaryMemberMetadata_GetBinaryDataType(DummyHandle), NRT_BINTYPE_NULLORUNKNOWN);
}

TEST_F(InteropBinaryMemberMetadataTest, GetDataLocationReturnsCorrectLocation)
{
    EXPECT_EQ(Nrt_BinaryMemberMetadata_GetDataLocation(DummyHandle), 10);
}

TEST_F(InteropBinaryMemberMetadataTest, GetSizeOfTypeInBytesReturnsCorrectSize)
{
    EXPECT_EQ(Nrt_BinaryMemberMetadata_GetSizeOfTypeInBytes(DummyHandle), 20);
}

TEST_F(InteropBinaryMemberMetadataTest, GetLengthReturnsCorrectLength)
{
    EXPECT_EQ(Nrt_BinaryMemberMetadata_GetLength(DummyHandle), 30);
}

TEST_F(InteropBinaryMemberMetadataTest, GetSizeOfSerialisedDataInbytesReturnsCorrectSize)
{
    EXPECT_EQ(Nrt_BinaryMemberMetadata_GetSizeOfSerialisedDataInBytes(DummyHandle), 40);
}
