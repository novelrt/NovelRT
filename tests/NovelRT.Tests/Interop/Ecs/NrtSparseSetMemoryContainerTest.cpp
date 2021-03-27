// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT.h>

#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(InteropSparseSetMemoryContainerTest, InsertCopiesBytesProperly)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    auto dataView = Nrt_SparseSetMemoryContainer_Indexer(container, 0);
    int32_t result = 0;
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataView, &result);
    EXPECT_EQ(result, testValue);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataView);
    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, InsertCopiesBytesProperlyMultipleTimes)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValueOne = 10;
    int32_t testValueTwo = 20;
    int32_t testValueThree = 30;

    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValueOne), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValueTwo), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValueThree), NRT_SUCCESS);

    int32_t resultOne = 0;
    int32_t resultTwo = 0;
    int32_t resultThree = 0;

    auto dataViewOne = Nrt_SparseSetMemoryContainer_Indexer(container, 0);
    auto dataViewTwo = Nrt_SparseSetMemoryContainer_Indexer(container, 1);
    auto dataViewThree = Nrt_SparseSetMemoryContainer_Indexer(container, 2);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataViewOne, &resultOne);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataViewTwo, &resultTwo);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataViewThree, &resultThree);

    EXPECT_EQ(resultOne, testValueOne);
    EXPECT_EQ(resultOne, testValueOne);
    EXPECT_EQ(resultOne, testValueOne);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataViewOne);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataViewTwo);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataViewThree);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, InsertReturnsCorrectErrorCodeWhenDuplicateKeyEntered)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_FAILURE_DUPLICATE_KEY_PROVIDED);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, TryInsertCopiesBytesProperly)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryInsert(container, 0, &testValue), NRT_TRUE);
    auto dataView = Nrt_SparseSetMemoryContainer_Indexer(container, 0);
    int32_t result = 0;
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataView, &result);
    EXPECT_EQ(result, testValue);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataView);
    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, TryInsertCopiesBytesProperlyMultipleTimes)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValueOne = 10;
    int32_t testValueTwo = 20;
    int32_t testValueThree = 30;

    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryInsert(container, 0, &testValueOne), NRT_TRUE);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryInsert(container, 1, &testValueTwo), NRT_TRUE);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryInsert(container, 2, &testValueThree), NRT_TRUE);

    int32_t resultOne = 0;
    int32_t resultTwo = 0;
    int32_t resultThree = 0;

    auto dataViewOne = Nrt_SparseSetMemoryContainer_Indexer(container, 0);
    auto dataViewTwo = Nrt_SparseSetMemoryContainer_Indexer(container, 1);
    auto dataViewThree = Nrt_SparseSetMemoryContainer_Indexer(container, 2);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataViewOne, &resultOne);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataViewTwo, &resultTwo);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataViewThree, &resultThree);

    EXPECT_EQ(resultOne, testValueOne);
    EXPECT_EQ(resultOne, testValueOne);
    EXPECT_EQ(resultOne, testValueOne);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataViewOne);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataViewTwo);
    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataViewThree);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, TryInsertReturnsFalseWhenDuplicateKeyEntered)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryInsert(container, 0, &testValue), NRT_TRUE);
    EXPECT_EQ(Nrt_SparseSetMemoryContainer_TryInsert(container, 0, &testValue), NRT_FALSE);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, RemoveRemovesTheKeyCorrectly)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Remove(container, 0), NRT_SUCCESS);

    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Length(container), 0);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, RemoveRemovesTheKeyCorrectlyWhenMultipleValuesExist)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValue), NRT_SUCCESS);

    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Remove(container, 1), NRT_SUCCESS);

    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Length(container), 2);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, RemoveReturnsCorrectErrorCodeWhenDuplicateKeyremoved)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Remove(container, 0), NRT_SUCCESS);
    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Remove(container, 0), NRT_FAILURE_KEY_NOT_FOUND);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, TryRemoveRemovesTheKeyCorrectly)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryRemove(container, 0), NRT_TRUE);

    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Length(container), 0);
    EXPECT_EQ(Nrt_SparseSetMemoryContainer_ContainsKey(container, 0), NRT_FALSE);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, TryRemoveRemovesTheKeyCorrectlyWhenMultipleValuesExist)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValue), NRT_SUCCESS);

    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryRemove(container, 1), NRT_TRUE);

    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Length(container), 2);
    EXPECT_EQ(Nrt_SparseSetMemoryContainer_ContainsKey(container, 1), NRT_FALSE);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, TryRemoveReturnsFalseWhenDuplicateKeyRemoved)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryRemove(container, 0), NRT_TRUE);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_TryRemove(container, 0), NRT_FALSE);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, ClearRemovesAllEntries)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    Nrt_SparseSetMemoryContainer_Clear(container);

    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Length(container), 0);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, CopyKeybasedOnDenseIndexReturnsCorrectKey)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 3, &testValue), NRT_SUCCESS);
    size_t output = 0;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex(container, 0, &output), NRT_SUCCESS);
    EXPECT_EQ(output, 3);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, CopyKeybasedOnDenseIndexReturnsCorrectErrorCodeWhenKeyDoesNotExist)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));

    size_t output = 0;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex(container, 0, &output),
              NRT_FAILURE_ARGUMENT_OUT_OF_RANGE);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, CopyKeybasedOnDenseIndexUnsafeReturnsCorrectKey)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 3, &testValue), NRT_SUCCESS);
    size_t output = Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe(container, 0);

    EXPECT_EQ(output, 3);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, LengthReturnsCorrectValue)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValue), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValue), NRT_SUCCESS);

    EXPECT_EQ(Nrt_SparseSetMemoryContainer_Length(container), 3);

    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, IndexerReturnsCorrectMutableByteIteratorView)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValueOne = 10;
    int32_t testValueTwo = 10;
    int32_t testValueThree = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValueOne), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValueTwo), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValueThree), NRT_SUCCESS);

    auto dataView = Nrt_SparseSetMemoryContainer_Indexer(container, 1);

    int32_t result = 0;
    Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(dataView, &result);

    EXPECT_EQ(result, testValueTwo);

    Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(dataView);
    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, ConstIndexerReturnsCorrectConstByteIteratorView)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValueOne = 10;
    int32_t testValueTwo = 10;
    int32_t testValueThree = 10;
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValueOne), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValueTwo), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValueThree), NRT_SUCCESS);

    auto dataView = Nrt_SparseSetMemoryContainer_ConstIndexer(container, 1);

    int32_t result = 0;
    Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation(dataView, &result);

    EXPECT_EQ(result, testValueTwo);

    Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(dataView);
    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, IteratingTheMutableCollectionReturnsCorrectValues)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValueOne = 10;
    int32_t testValueTwo = 10;
    int32_t testValueThree = 10;

    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValueOne), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValueTwo), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValueThree), NRT_SUCCESS);

    NrtSparseSetMemoryContainer_IteratorHandle begin = nullptr;
    NrtSparseSetMemoryContainer_IteratorHandle end = Nrt_SparseSetMemoryContainer_end(container);

    for (begin = Nrt_SparseSetMemoryContainer_begin(container);
         Nrt_SparseSetMemoryContainer_Iterator_NotEqual(begin, end);
         Nrt_SparseSetMemoryContainer_Iterator_MoveNext(begin))
    {
        size_t key = 0;
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle value = nullptr;
        Nrt_SparseSetMemoryContainer_Iterator_GetValuePair(begin, &key, &value);
        int32_t result =
            *reinterpret_cast<int32_t*>(Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(value));

        EXPECT_EQ(10, result);

        Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(value);
    }

    Nrt_SparseSetMemoryContainer_Iterator_Destroy(begin);
    Nrt_SparseSetMemoryContainer_Iterator_Destroy(end);
    Nrt_SparseSetMemoryContainer_Destroy(container);
}

TEST(InteropSparseSetMemoryContainerTest, IteratingTheConstCollectionReturnsCorrectValues)
{
    auto container = Nrt_SparseSetMemoryContainer_Create(sizeof(int32_t));
    int32_t testValueOne = 10;
    int32_t testValueTwo = 10;
    int32_t testValueThree = 10;

    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 0, &testValueOne), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 1, &testValueTwo), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SparseSetMemoryContainer_Insert(container, 2, &testValueThree), NRT_SUCCESS);

    NrtSparseSetMemoryContainer_ConstIteratorHandle begin = nullptr;
    NrtSparseSetMemoryContainer_ConstIteratorHandle end = Nrt_SparseSetMemoryContainer_cend(container);

    for (begin = Nrt_SparseSetMemoryContainer_cbegin(container);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(begin, end);
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(begin))
    {
        size_t key = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle value = nullptr;
        Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(begin, &key, &value);
        int32_t result =
            *reinterpret_cast<const int32_t*>(Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle(value));

        EXPECT_EQ(10, result);

        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(value);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(begin);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(end);
    Nrt_SparseSetMemoryContainer_Destroy(container);
}
